#include <u.h>
#include <libc.h>

void
main(void)
{
	print("ushort %.8lux\n", signof(ushort));
	print("uchar %.8lux\n", signof(uchar));
	print("ulong %.8lux\n", signof(ulong));
	print("uint %.8lux\n", signof(uint));
	print("schar %.8lux\n", signof(schar));
	print("vlong %.8lux\n", signof(vlong));
	print("uvlong %.8lux\n", signof(uvlong));
	print("intptr %.8lux\n", signof(intptr));
	print("uintptr %.8lux\n", signof(uintptr));
	print("usize %.8lux\n", signof(usize));
	print("Rune %.8lux\n", signof(Rune));
	print("FPdbleword %.8lux\n", signof(FPdbleword));
	print("jmp_buf %.8lux\n", signof(jmp_buf));
	print("mpdigit %.8lux\n", signof(mpdigit));
	print("u8int %.8lux\n", signof(u8int));
	print("u16int %.8lux\n", signof(u16int));
	print("u32int %.8lux\n", signof(u32int));
	print("u64int %.8lux\n", signof(u64int));
	print("s8int %.8lux\n", signof(s8int));
	print("s16int %.8lux\n", signof(s16int));
	print("s32int %.8lux\n", signof(s32int));
	print("s64int %.8lux\n", signof(s64int));
	print("va_list %.8lux\n", signof(va_list));
	print("union FPdbleword %.8lux\n", signof(union FPdbleword));
	exits(nil);
}
