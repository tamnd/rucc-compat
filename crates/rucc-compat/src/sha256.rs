//! SHA-256, so that a fetched tarball is the tarball the manifest names.
//!
//! FIPS 180-4, written out rather than depended on. The whole point of the hash here is that
//! it is checked before anything is unpacked, and a check that arrives through a supply chain
//! is a check that has the same problem it is supposed to solve.

/// The round constants, the first thirty two bits of the cube roots of the first sixty four
/// primes.
const K: [u32; 64] = [
    0x428a_2f98,
    0x7137_4491,
    0xb5c0_fbcf,
    0xe9b5_dba5,
    0x3956_c25b,
    0x59f1_11f1,
    0x923f_82a4,
    0xab1c_5ed5,
    0xd807_aa98,
    0x1283_5b01,
    0x2431_85be,
    0x550c_7dc3,
    0x72be_5d74,
    0x80de_b1fe,
    0x9bdc_06a7,
    0xc19b_f174,
    0xe49b_69c1,
    0xefbe_4786,
    0x0fc1_9dc6,
    0x240c_a1cc,
    0x2de9_2c6f,
    0x4a74_84aa,
    0x5cb0_a9dc,
    0x76f9_88da,
    0x983e_5152,
    0xa831_c66d,
    0xb003_27c8,
    0xbf59_7fc7,
    0xc6e0_0bf3,
    0xd5a7_9147,
    0x06ca_6351,
    0x1429_2967,
    0x27b7_0a85,
    0x2e1b_2138,
    0x4d2c_6dfc,
    0x5338_0d13,
    0x650a_7354,
    0x766a_0abb,
    0x81c2_c92e,
    0x9272_2c85,
    0xa2bf_e8a1,
    0xa81a_664b,
    0xc24b_8b70,
    0xc76c_51a3,
    0xd192_e819,
    0xd699_0624,
    0xf40e_3585,
    0x106a_a070,
    0x19a4_c116,
    0x1e37_6c08,
    0x2748_774c,
    0x34b0_bcb5,
    0x391c_0cb3,
    0x4ed8_aa4a,
    0x5b9c_ca4f,
    0x682e_6ff3,
    0x748f_82ee,
    0x78a5_636f,
    0x84c8_7814,
    0x8cc7_0208,
    0x90be_fffa,
    0xa450_6ceb,
    0xbef9_a3f7,
    0xc671_78f2,
];

/// A hash being computed over a stream.
#[derive(Debug, Clone)]
pub struct Sha256 {
    state: [u32; 8],
    buffer: [u8; 64],
    buffered: usize,
    length: u64,
}

impl Default for Sha256 {
    fn default() -> Sha256 {
        Sha256::new()
    }
}

impl Sha256 {
    /// A hash of nothing so far.
    #[must_use]
    pub fn new() -> Sha256 {
        Sha256 {
            state: [
                0x6a09_e667,
                0xbb67_ae85,
                0x3c6e_f372,
                0xa54f_f53a,
                0x510e_527f,
                0x9b05_688c,
                0x1f83_d9ab,
                0x5be0_cd19,
            ],
            buffer: [0; 64],
            buffered: 0,
            length: 0,
        }
    }

    /// Adds bytes.
    pub fn update(&mut self, mut data: &[u8]) {
        self.length = self.length.wrapping_add(data.len() as u64);
        if self.buffered > 0 {
            let want = 64 - self.buffered;
            let take = want.min(data.len());
            self.buffer[self.buffered..self.buffered + take].copy_from_slice(&data[..take]);
            self.buffered += take;
            data = &data[take..];
            if self.buffered < 64 {
                // All of it went into the buffer and there is no whole block yet. Falling
                // through here would run the tail of this function over an empty slice and
                // set the count back to zero, which loses everything buffered so far.
                return;
            }
            let block = self.buffer;
            self.block(&block);
            self.buffered = 0;
        }
        let mut chunks = data.chunks_exact(64);
        for chunk in &mut chunks {
            let mut block = [0u8; 64];
            block.copy_from_slice(chunk);
            self.block(&block);
        }
        let rest = chunks.remainder();
        self.buffer[..rest.len()].copy_from_slice(rest);
        self.buffered = rest.len();
    }

    /// The digest, lowercase hexadecimal, which is how a manifest writes it.
    #[must_use]
    pub fn hex(mut self) -> String {
        let bits = self.length.wrapping_mul(8);
        self.update(&[0x80]);
        // The length is added after the padding, and `update` has already counted the bytes
        // it wrote, so the count is taken above rather than read back here.
        while self.buffered != 56 {
            self.update(&[0]);
        }
        let block = {
            let mut block = self.buffer;
            block[56..].copy_from_slice(&bits.to_be_bytes());
            block
        };
        self.block(&block);
        let mut out = String::with_capacity(64);
        for word in self.state {
            out.push_str(&format!("{word:08x}"));
        }
        out
    }

    fn block(&mut self, block: &[u8; 64]) {
        let mut w = [0u32; 64];
        for (at, word) in w.iter_mut().take(16).enumerate() {
            let bytes = [block[at * 4], block[at * 4 + 1], block[at * 4 + 2], block[at * 4 + 3]];
            *word = u32::from_be_bytes(bytes);
        }
        for at in 16..64 {
            let s0 = w[at - 15].rotate_right(7) ^ w[at - 15].rotate_right(18) ^ (w[at - 15] >> 3);
            let s1 = w[at - 2].rotate_right(17) ^ w[at - 2].rotate_right(19) ^ (w[at - 2] >> 10);
            w[at] = w[at - 16].wrapping_add(s0).wrapping_add(w[at - 7]).wrapping_add(s1);
        }
        let [mut a, mut b, mut c, mut d, mut e, mut f, mut g, mut h] = self.state;
        for at in 0..64 {
            let s1 = e.rotate_right(6) ^ e.rotate_right(11) ^ e.rotate_right(25);
            let choice = (e & f) ^ (!e & g);
            let t1 =
                h.wrapping_add(s1).wrapping_add(choice).wrapping_add(K[at]).wrapping_add(w[at]);
            let s0 = a.rotate_right(2) ^ a.rotate_right(13) ^ a.rotate_right(22);
            let majority = (a & b) ^ (a & c) ^ (b & c);
            let t2 = s0.wrapping_add(majority);
            h = g;
            g = f;
            f = e;
            e = d.wrapping_add(t1);
            d = c;
            c = b;
            b = a;
            a = t1.wrapping_add(t2);
        }
        for (slot, value) in self.state.iter_mut().zip([a, b, c, d, e, f, g, h]) {
            *slot = slot.wrapping_add(value);
        }
    }
}

/// The digest of a slice, for when there is no stream to speak of.
#[must_use]
pub fn hex(data: &[u8]) -> String {
    let mut hash = Sha256::new();
    hash.update(data);
    hash.hex()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn the_empty_input_is_the_published_digest() {
        assert_eq!(hex(b""), "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    }

    #[test]
    fn abc_is_the_digest_in_the_standard() {
        assert_eq!(hex(b"abc"), "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
    }

    #[test]
    fn a_multi_block_input_is_the_digest_in_the_standard() {
        let input = b"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
        assert_eq!(hex(input), "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
    }

    #[test]
    fn feeding_it_a_byte_at_a_time_gives_the_same_answer() {
        let input = b"the quick brown fox jumps over the lazy dog, twice, and then some more";
        let mut hash = Sha256::new();
        for byte in input {
            hash.update(&[*byte]);
        }
        assert_eq!(hash.hex(), hex(input));
    }

    #[test]
    fn a_million_letters_is_the_digest_in_the_standard() {
        let mut hash = Sha256::new();
        let chunk = vec![b'a'; 1000];
        for _ in 0..1000 {
            hash.update(&chunk);
        }
        assert_eq!(hash.hex(), "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0");
    }
}
