/* verdict: accept */
int main(void) { return _Generic(1L, long: 0, default: 1); }
