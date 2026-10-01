/* verdict: accept */
struct s { int n; int a[0]; };
int main(void) { return (int)sizeof(struct s) - (int)sizeof(int); }
