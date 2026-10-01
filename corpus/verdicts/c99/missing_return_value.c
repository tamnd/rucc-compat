/* verdict: reject */
/* error: 'return' with no value, in function returning non-void */
int f(void) { return; }
int main(void) { return f(); }
