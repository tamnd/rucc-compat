/* C89 enumerations and tags: implicit and explicit enumerator values, negative values, enumerators
 * used as constants, a structure declared before it is complete, and a self-referential list. */
#include <stdio.h>

enum color { RED, GREEN = 5, BLUE, NEGATIVE = -2, AFTER };
enum { ANON_A = 3, ANON_B = ANON_A * 2 };

struct node;
struct list { struct node *head; };
struct node { int value; struct node *next; };

int main(void)
{
    enum color c = BLUE;
    int table[ANON_B];
    struct node n3, n2, n1;
    struct list l;
    struct node *it;
    int sum = 0;
    printf("%d %d %d %d %d\n", RED, GREEN, BLUE, NEGATIVE, AFTER);
    printf("%d %lu\n", c, (unsigned long)sizeof table / sizeof table[0]);
    switch (c) {
    case BLUE: printf("blue\n"); break;
    default: printf("other\n");
    }
    n1.value = 1; n1.next = &n2;
    n2.value = 2; n2.next = &n3;
    n3.value = 3; n3.next = 0;
    l.head = &n1;
    for (it = l.head; it; it = it->next)
        sum = sum * 10 + it->value;
    printf("%d\n", sum);
    printf("%d\n", (int)sizeof(enum color) == (int)sizeof(int));
    return 0;
}
