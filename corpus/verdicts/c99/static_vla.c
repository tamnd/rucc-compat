/* verdict: reject */
/* error: storage size of 'a' isn't constant */
int main(int n, char **v) { (void)v; static int a[n]; return 0; }
