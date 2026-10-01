/* verdict: reject */
/* error: assignment to expression with array type */
int main(void) { int a[2], b[2] = {0}; a = b; return a[0]; }
