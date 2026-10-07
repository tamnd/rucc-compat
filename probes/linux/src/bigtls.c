__thread char big[65536];
int touch(int i) { big[i] = 1; return big[i]; }
