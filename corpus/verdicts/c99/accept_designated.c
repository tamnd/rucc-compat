/* verdict: accept */
struct s { int a, b; };
int main(void) { struct s x = {.b = 2, .a = 1}; return x.a + x.b - 3; }
