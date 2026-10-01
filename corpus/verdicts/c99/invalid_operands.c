/* verdict: reject */
/* error: invalid operands to binary + (have 'struct s' and 'int') */
struct s { int a; };
int main(void) { struct s x = {1}; return x + 1; }
