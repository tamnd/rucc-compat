/* verdict: reject */
/* error: '_Alignas' specifiers cannot reduce alignment of 'x' */
_Alignas(1) int x;
int main(void) { return x; }
