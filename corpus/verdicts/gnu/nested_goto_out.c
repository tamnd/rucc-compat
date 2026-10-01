/* verdict: reject */
/* error: label 'out' used but not defined */
int main(void) { int f(void) { goto out; return 0; } f(); out: return 0; }
