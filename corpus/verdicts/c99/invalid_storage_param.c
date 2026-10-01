/* verdict: reject */
/* error: storage class specified for parameter 'a' */
int f(static int a) { return a; }
int main(void) { return f(0); }
