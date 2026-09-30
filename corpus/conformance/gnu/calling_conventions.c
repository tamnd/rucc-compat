/* The 32-bit calling conventions and the Windows linkage attributes. On an x86-64 ELF target
   GCC reads each one, warns that it does not apply, and builds the function as if it were not
   there, so the program runs the same either way. */
#include <stdio.h>

__attribute__((cdecl)) static int c1(int a) { return a + 1; }
__attribute__((stdcall)) static int c2(int a) { return a + 2; }
__attribute__((fastcall)) static int c3(int a) { return a + 3; }
__attribute__((thiscall)) static int c4(int a) { return a + 4; }
__attribute__((regparm(3))) static int c5(int a) { return a + 5; }
__attribute__((vectorcall)) static int c6(int a) { return a + 6; }
__attribute__((dllexport)) int exported(void) { return 7; }
__attribute__((dllimport)) extern int imported_nowhere;
__attribute__((selectany)) int chosen = 8;

int main(void)
{
    printf("conventions %d %d %d %d %d %d\n", c1(0), c2(0), c3(0), c4(0), c5(0), c6(0));
    printf("linkage %d %d\n", exported(), chosen);
    return 0;
}
