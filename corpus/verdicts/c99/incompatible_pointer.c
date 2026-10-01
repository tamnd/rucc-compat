/* verdict: reject */
/* error: initialization of 'float *' from incompatible pointer type 'int *' */
int main(void) { int i = 0; float *p = &i; return *p != 0; }
