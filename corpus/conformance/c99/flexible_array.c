// C99 flexible array members: the last member of a structure an array of no length, the size of
// the structure leaving it out, and storage for it allocated with the structure.
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct message {
    int length;
    char text[];
};

struct numbers {
    short count;
    long values[];
};

int main(void)
{
    struct message *m = malloc(sizeof *m + 6);
    m->length = 5;
    for (int i = 0; i < 5; i++)
        m->text[i] = (char)('a' + i);
    m->text[5] = '\0';
    printf("%d %s\n", m->length, m->text);
    printf("%zu %zu\n", sizeof(struct message), offsetof(struct message, text));
    printf("%zu %zu\n", sizeof(struct numbers), offsetof(struct numbers, values));
    free(m);
    return 0;
}
