/* verdict: reject */
/* error: '_Generic' selector of type 'double' is not compatible with any association */
int main(void) { return _Generic(1.0, int: 0); }
