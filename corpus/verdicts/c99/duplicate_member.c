/* verdict: reject */
/* error: duplicate member 'a' */
struct s { int a; int a; };
int main(void) { return 0; }
