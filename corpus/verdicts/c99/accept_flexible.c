/* verdict: accept */
struct s { int n; int a[]; };
int main(void) { return (int)sizeof(struct s) - (int)sizeof(int); }
