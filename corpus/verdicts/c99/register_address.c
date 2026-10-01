/* verdict: reject */
/* error: address of register variable 'r' requested */
int main(void) { register int r = 0; int *p = &r; return *p; }
