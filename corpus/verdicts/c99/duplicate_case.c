/* verdict: reject */
/* error: duplicate case value */
int main(void) { switch (0) { case 1: case 1: break; } return 0; }
