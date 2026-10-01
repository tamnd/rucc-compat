/* verdict: accept */
int main(void) { switch (3) { case 1 ... 5: return 0; } return 1; }
