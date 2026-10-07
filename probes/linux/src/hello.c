#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) { char buf[16]; strcpy(buf, "linux"); printf("hello %s %zu %zu\n", buf, sizeof(long), sizeof(long double)); return 0; }
