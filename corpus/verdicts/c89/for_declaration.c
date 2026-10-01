/* verdict: reject */
/* error: 'for' loop initial declarations are only allowed in C99 or C11 mode */
int main(void) { for (int i = 0; i < 1; i++) ; return 0; }
