#!/usr/bin/env bash
# A FreeBSD 15.1 VM on a Linux host with KVM. The bsd-predef and bsd-abi reference jobs use it.
#
#   freebsd-vm.sh up        download and check the image, boot it, and wait for ssh
#   freebsd-vm.sh ssh CMD   run CMD as root in the VM
#   freebsd-vm.sh down      power off the VM
#
# The image is the official FreeBSD 15.1-RELEASE BASIC-CI image. It is the builder image of tamnd/rucc-bsd
# (conf/freebsd/builder.conf), with the same SHA-256. The image lets root log in with an empty password.
# The first login installs a key, and every later call uses the key.
set -euo pipefail

name=FreeBSD-15.1-RELEASE-amd64-BASIC-CI-ufs.raw.xz
url=https://download.freebsd.org/releases/CI-IMAGES/15.1-RELEASE/amd64/Latest/$name
sha256=908e735f18ba192eaf48c2703b549225c9b96e74e3784bd9278c7120b4139962

: "${VM_CACHE:=$HOME/.cache/rucc-compat-bsd}"
: "${VM_DIR:=/mnt/freebsd-vm}"
: "${VM_CPUS:=$(nproc)}"
: "${VM_MEM:=8G}"
: "${VM_PORT:=2222}"

key="$VM_DIR/id_ed25519"
ssh_opts=(-o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -o LogLevel=ERROR
	-o ServerAliveInterval=30 -o ServerAliveCountMax=20 -p "$VM_PORT")

vm_ssh() {
	ssh "${ssh_opts[@]}" -i "$key" -o BatchMode=yes root@127.0.0.1 "$@"
}

up() {
	mkdir -p "$VM_CACHE" "$VM_DIR"
	local xz="$VM_CACHE/$name"
	if [ ! -f "$xz" ] || ! echo "$sha256  $xz" | sha256sum -c --status -; then
		curl -sfL --retry 3 -o "$xz.part" "$url"
		mv "$xz.part" "$xz"
	fi
	echo "$sha256  $xz" | sha256sum -c -
	xz -dc -T0 "$xz" > "$VM_DIR/root.raw"
	# growfs in the image grows the root file system to this size at the first boot.
	truncate -s 16G "$VM_DIR/root.raw"
	rm -f "$key" "$key.pub"
	ssh-keygen -q -t ed25519 -N '' -f "$key"
	qemu-system-x86_64 -machine q35,accel=kvm -cpu host -smp "$VM_CPUS" -m "$VM_MEM" \
		-drive if=virtio,file="$VM_DIR/root.raw",format=raw,cache=unsafe,discard=unmap \
		-netdev user,id=n0,hostfwd=tcp:127.0.0.1:"$VM_PORT"-:22 -device virtio-net-pci,netdev=n0 \
		-display none -serial file:"$VM_DIR/console.log" \
		-pidfile "$VM_DIR/qemu.pid" -daemonize
	local i
	for i in $(seq 1 60); do
		echo "ssh try $i"
		if sshpass -p '' ssh "${ssh_opts[@]}" -o PubkeyAuthentication=no -o ConnectTimeout=5 \
			root@127.0.0.1 'mkdir -p -m 700 .ssh && cat >> .ssh/authorized_keys' < "$key.pub" 2>/dev/null; then
			vm_ssh 'uname -a'
			return 0
		fi
		sleep 10
	done
	echo "the VM did not answer on ssh in 10 minutes" >&2
	tail -50 "$VM_DIR/console.log" >&2 || true
	return 1
}

down() {
	[ -f "$VM_DIR/qemu.pid" ] || return 0
	local pid
	pid="$(cat "$VM_DIR/qemu.pid")"
	vm_ssh 'shutdown -p now' > /dev/null 2>&1 || true
	for _ in $(seq 1 60); do
		kill -0 "$pid" 2> /dev/null || return 0
		sleep 2
	done
	kill "$pid" 2> /dev/null || true
}

case "${1:-}" in
	up) up ;;
	down) down ;;
	ssh) shift; vm_ssh "$@" ;;
	*) echo "usage: $0 up | down | ssh CMD" >&2; exit 2 ;;
esac
