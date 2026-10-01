/* verdict: reject */
/* error: 'typeof' applied to a bit-field */
struct s { int a : 3; } v;
typeof(v.a) y;
int main(void) { return 0; }
