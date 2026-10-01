/* verdict: reject */
/* error: initialization of 'int *' from 'int' makes pointer from integer without a cast */
int main(void) { int *p = 5; return p != 0; }
