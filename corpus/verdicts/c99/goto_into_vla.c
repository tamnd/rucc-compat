/* verdict: reject */
/* error: jump into scope of identifier with variably modified type */
int main(int n, char **v) { (void)v; goto in; { int a[n]; in: a[0] = 0; return a[0]; } }
