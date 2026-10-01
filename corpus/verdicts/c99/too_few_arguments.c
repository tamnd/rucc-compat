/* verdict: reject */
/* error: too few arguments to function 'f'; expected 2, have 1 */
int f(int a, int b) { return a + b; }
int main(void) { return f(1); }
