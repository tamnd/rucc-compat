/* verdict: accept */
struct s { union { int a; float f; }; };
int main(void) { struct s x = {{0}}; return x.a; }
