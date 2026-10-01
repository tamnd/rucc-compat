/* verdict: reject */
/* error: 'constexpr' integer initializer is not an integer constant expression */
int main(void) { constexpr int x = 1.5; return x; }
