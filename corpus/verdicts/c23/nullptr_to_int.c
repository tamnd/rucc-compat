/* verdict: reject */
/* error: incompatible types when initializing type 'int' using type 'typeof (nullptr)' */
int main(void) { int x = nullptr; return x; }
