int old_f(void) { return 1; }
int new_f(void) { return 2; }
__asm__(".symver old_f,f@VERS_1");
__asm__(".symver new_f,f@@VERS_2");
