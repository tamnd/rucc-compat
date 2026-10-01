/* verdict: reject */
/* error: initializer element is not constant */
int f(void);
int x = f();
int main(void) { return x; }
