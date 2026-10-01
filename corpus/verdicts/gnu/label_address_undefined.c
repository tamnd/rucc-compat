/* verdict: reject */
/* error: label 'nowhere' used but not defined */
int main(void) { void *p = &&nowhere; return p != 0; }
