/* verdict: reject */
/* error: 'struct s' has no member named 'b' */
struct s { int a; };
int main(void) { struct s x = {0}; return x.b; }
