/* verdict: reject */
/* error: flexible array member not at end of struct */
struct s { int n; int a[]; int b; };
int main(void) { return 0; }
