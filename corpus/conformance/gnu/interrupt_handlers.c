/* An x86 interrupt handler and a function that saves every register, which rucc refuses until
   it can build them, tamnd/rucc#2480. Nothing calls them: an interrupt handler returns with
   iret, so the program only checks that both are built and have addresses. */
#include <stdio.h>

#if defined __x86_64__
struct interrupt_frame;
__attribute__((interrupt, target("general-regs-only"))) void handler(struct interrupt_frame *frame) { (void)frame; }
__attribute__((no_caller_saved_registers, target("general-regs-only"))) void saves_everything(void) {}
#define BUILT (handler != 0 && saves_everything != 0)
#else
#define BUILT 1
#endif

int main(void)
{
    printf("built %d\n", BUILT);
    return 0;
}
