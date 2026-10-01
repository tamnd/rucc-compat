/* verdict: reject */
/* error: '_Generic' specifies two compatible types */
int main(void) { return _Generic(1, int: 0, int: 1); }
