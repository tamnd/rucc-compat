/* verdict: accept */
int f();
int f(int);
int f(int a) { return a; }
int main(void) { return f(0); }
