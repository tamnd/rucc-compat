/* verdict: reject */
/* error: void value not ignored as it ought to be */
void f(void) {}
int main(void) { int x = f(); return x; }
