/* verdict: reject */
/* error: function-scope 'x' implicitly auto and declared '_Thread_local' */
int main(void) { _Thread_local int x = 0; return x; }
