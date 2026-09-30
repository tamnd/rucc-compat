/* Whether the machine has the CRC32 instructions, asked the way Postgres asks in
 * src/port/pg_crc32c_armv8_choose.c: the HWCAP_CRC32 bit of the auxiliary vector on Linux. Every
 * Apple arm64 processor has them, so macOS is not asked. */

#ifndef INTRINSICS_ARM_H
#define INTRINSICS_ARM_H

#ifdef __linux__
#include <sys/auxv.h>
#ifndef HWCAP_CRC32
#define HWCAP_CRC32 (1 << 7)
#endif
static int have_crc32(void) { return (getauxval(AT_HWCAP) & HWCAP_CRC32) != 0; }
#else
static int have_crc32(void) { return 1; }
#endif

#endif
