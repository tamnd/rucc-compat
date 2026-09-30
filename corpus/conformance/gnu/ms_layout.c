/* ms_struct and gcc_struct pick between Microsoft's bit-field layout and GCC's for one record,
   which GCC honours on every x86 target. */
#include <stdio.h>

struct __attribute__((ms_struct)) ms { char c; int bits : 4; char d; };
struct __attribute__((gcc_struct)) gnu { char c; int bits : 4; char d; };

int main(void)
{
    printf("ms_struct %d\n", (int)sizeof(struct ms));
    printf("gcc_struct %d\n", (int)sizeof(struct gnu));
    return 0;
}
