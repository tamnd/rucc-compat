/* verdict: reject */
/* error: invalid application of 'sizeof' to incomplete type 'struct s' */
struct s;
int main(void) { return sizeof(struct s); }
