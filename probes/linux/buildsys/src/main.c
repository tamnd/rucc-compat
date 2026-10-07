#include <pthread.h>
#include <stdio.h>
#include "fix.h"

static void *work(void *p) {
	(void)p;
	fix_calls();
	return NULL;
}

int main(void) {
	pthread_t t;
	pthread_create(&t, NULL, work, NULL);
	pthread_join(t, NULL);
	printf("%d %.1f\n", fix_calls(), fix_hyp(3, 4));
	return 0;
}
