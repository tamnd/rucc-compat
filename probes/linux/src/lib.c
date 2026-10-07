#include <stdio.h>
__thread int tls_counter = 40;
static int hidden_helper(int x) { return x + 1; }
__attribute__((visibility("hidden"))) int also_hidden(int x) { return x * 2; }
int lib_add(int x) { tls_counter++; return hidden_helper(x) + also_hidden(x) + tls_counter; }
extern int lib_data; int lib_data = 7;
