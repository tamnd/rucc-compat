/* verdict: reject */
/* error: static assertion failed: "one is not two" */
_Static_assert(1 == 2, "one is not two");
int main(void) { return 0; }
