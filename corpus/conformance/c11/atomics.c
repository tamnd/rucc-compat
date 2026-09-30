// C11 atomics: the _Atomic qualifier and specifier, <stdatomic.h> load, store, exchange,
// compare and exchange and the fetch operations, atomic_flag, the lock free macros, and compound
// assignment and increment on an atomic object being one atomic operation. The operations take
// an atomic structure as well as an arithmetic type.
#include <stdio.h>
#include <stdbool.h>
#include <stdatomic.h>

struct pair { int a, b; };

int main(void)
{
    _Atomic int a = 5;
    atomic_int b = ATOMIC_VAR_INIT(1);
    _Atomic(long) c = 100;
    a += 3;
    a++;
    printf("%d\n", atomic_load(&a));
    atomic_store(&b, 7);
    int old = atomic_exchange(&b, 8);
    printf("%d %d\n", old, atomic_load_explicit(&b, memory_order_acquire));
    int expected = 8;
    bool swapped = atomic_compare_exchange_strong(&b, &expected, 20);
    printf("%d %d\n", swapped, b);
    expected = 0;
    swapped = atomic_compare_exchange_weak(&b, &expected, 30);
    printf("%d %d\n", swapped, expected);
    long before = atomic_fetch_add(&c, 5);
    long middle = atomic_fetch_sub(&c, 2);
    printf("%ld %ld %ld\n", before, middle, atomic_load(&c));
    long ored = atomic_fetch_or(&c, 0x100);
    long anded = atomic_fetch_and(&c, 0xff);
    printf("%ld %ld %ld\n", ored, anded, atomic_load(&c));
    atomic_flag f = ATOMIC_FLAG_INIT;
    bool first = atomic_flag_test_and_set(&f);
    bool second = atomic_flag_test_and_set(&f);
    printf("%d %d\n", first, second);
    atomic_flag_clear(&f);
    printf("%d\n", atomic_flag_test_and_set(&f));
    printf("%d %d\n", ATOMIC_INT_LOCK_FREE, atomic_is_lock_free(&c));
    _Atomic struct pair p = { 1, 2 };
    struct pair q = p;
    printf("%d %d\n", q.a, q.b);
    atomic_store(&p, (struct pair){ 3, 4 });
    struct pair r = atomic_exchange(&p, (struct pair){ 5, 6 });
    struct pair want = { 5, 6 };
    bool moved = atomic_compare_exchange_strong(&p, &want, (struct pair){ 7, 8 });
    struct pair now = atomic_load(&p);
    printf("%d %d %d %d %d\n", r.a, r.b, moved, now.a, now.b);
    atomic_thread_fence(memory_order_seq_cst);
    return 0;
}
