#include <string.h>
#include <stdio.h>
int main(int argc, char **argv) { char d[8]; memcpy(d, argv[0], argc + 3); d[7] = 0; char s[8]; snprintf(s, sizeof s, "%d", argc); printf("%s %s\n", d, s); return 0; }
