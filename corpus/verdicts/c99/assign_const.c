/* verdict: reject */
/* error: assignment of read-only variable 'c' */
int main(void) { const int c = 1; c = 2; return c; }
