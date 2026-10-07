#include <math.h>
#include "fix.h"

static _Thread_local int calls;

int fix_calls(void) { return ++calls; }

double fix_hyp(double a, double b) { return sqrt(a * a + b * b); }
