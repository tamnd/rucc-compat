/* verdict: reject */
/* error: initializer element is not constant */
int f(void);
int main(void) { constexpr int x = f(); return x; }
