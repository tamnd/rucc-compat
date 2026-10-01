/* verdict: reject */
/* error: width of 'a' exceeds its type */
struct s { int a : 40; };
int main(void) { return 0; }
