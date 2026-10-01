/* verdict: reject */
/* error: 'return' with a value, in function returning void */
void f(void) { return 1; }
int main(void) { f(); return 0; }
