/* What __has_attribute answers for the attributes rucc builds but still answers no for, because
   the answer depends on the target (tamnd/rucc#2481) or because part of what the attribute asks
   for is missing: format (#2482), retain (#2483), optimize (#2484), zero_call_used_regs
   (#2335), target_clones (#2496), sentinel and designated_init (#2497), copy (#2498) and
   alloc_size (#2499). A header takes its fallback path on a no, so the answer is part of the
   feature. */
#include <stdio.h>

#define ASK(name) printf("%-20s %d\n", #name, __has_attribute(name))

int main(void)
{
    ASK(cdecl);
    ASK(stdcall);
    ASK(fastcall);
    ASK(thiscall);
    ASK(regparm);
    ASK(vectorcall);
    ASK(ms_struct);
    ASK(gcc_struct);
    ASK(dllimport);
    ASK(dllexport);
    ASK(selectany);
    ASK(format);
    ASK(retain);
    ASK(optimize);
    ASK(zero_call_used_regs);
    ASK(target_clones);
    ASK(sentinel);
    ASK(designated_init);
    ASK(copy);
    ASK(alloc_size);
    return 0;
}
