/* verdict: reject */
/* error: too many arguments to function 'f'; expected 1, have 2 */
int f(int a) { return a; }
int main(void) { return f(1, 2); }
