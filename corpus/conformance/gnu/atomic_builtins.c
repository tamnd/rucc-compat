/* The __atomic builtins, which take a memory order, and the older __sync ones, which are all
   sequentially consistent. One thread is enough to see that each does the arithmetic it says
   and hands back the value it says, the old one or the new one. */
#include <stdio.h>

struct pair { int a, b; };

int main(void)
{
    int v = 10, got, want, old;
    __atomic_store_n(&v, 20, __ATOMIC_RELEASE);
    printf("load %d\n", __atomic_load_n(&v, __ATOMIC_ACQUIRE));
    int nine = 9;
    __atomic_store(&v, &nine, __ATOMIC_SEQ_CST);
    __atomic_load(&v, &got, __ATOMIC_RELAXED);
    printf("generic load %d\n", got);
    printf("exchange %d %d\n", __atomic_exchange_n(&v, 30, __ATOMIC_ACQ_REL), v);
    int put = 31;
    __atomic_exchange(&v, &put, &old, __ATOMIC_SEQ_CST);
    printf("generic exchange %d %d\n", old, v);
    want = 31;
    int swapped = __atomic_compare_exchange_n(&v, &want, 40, 0, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED);
    want = 0;
    int missed = __atomic_compare_exchange_n(&v, &want, 50, 1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED);
    printf("compare exchange %d %d %d %d\n", swapped, missed, want, v);
    int desired = 41;
    want = 40;
    printf("generic compare exchange %d %d\n", __atomic_compare_exchange(&v, &want, &desired, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST), v);
    struct pair p = { 1, 2 }, q = { 3, 4 }, r;
    __atomic_exchange(&p, &q, &r, __ATOMIC_SEQ_CST);
    __atomic_load(&p, &q, __ATOMIC_SEQ_CST);
    printf("struct %d %d %d %d\n", r.a, r.b, q.a, q.b);
    unsigned u = 0xf0;
    printf("fetch %u %u %u %u %u %u %u\n", __atomic_fetch_add(&u, 1, 5), __atomic_fetch_sub(&u, 2, 5), __atomic_fetch_and(&u, 0xff, 5), __atomic_fetch_or(&u, 0x100, 5), __atomic_fetch_xor(&u, 1, 5), __atomic_fetch_nand(&u, 0xf, 5), u);
    u = 0xf0;
    printf("op fetch %u %u %u %u %u %u\n", __atomic_add_fetch(&u, 1, 5), __atomic_sub_fetch(&u, 2, 5), __atomic_and_fetch(&u, 0xff, 5), __atomic_or_fetch(&u, 0x100, 5), __atomic_xor_fetch(&u, 1, 5), __atomic_nand_fetch(&u, 0xf, 5));
    _Bool flag = 0;
    int first = __atomic_test_and_set(&flag, __ATOMIC_SEQ_CST);
    int second = __atomic_test_and_set(&flag, __ATOMIC_SEQ_CST);
    __atomic_clear(&flag, __ATOMIC_SEQ_CST);
    printf("test and set %d %d %d\n", first, second, flag);
    __atomic_thread_fence(__ATOMIC_SEQ_CST);
    __atomic_signal_fence(__ATOMIC_SEQ_CST);
    printf("lock free %d %d %d\n", __atomic_always_lock_free(sizeof(int), 0), __atomic_always_lock_free(64, 0), __atomic_is_lock_free(sizeof(long), &v));
    long s = 100;
    __sync_synchronize();
    printf("sync fetch %ld %ld %ld %ld %ld %ld %ld\n", __sync_fetch_and_add(&s, 5), __sync_fetch_and_sub(&s, 3), __sync_fetch_and_or(&s, 0x100), __sync_fetch_and_and(&s, 0x1ff), __sync_fetch_and_xor(&s, 1), __sync_fetch_and_nand(&s, 0xf), s);
    s = 100;
    printf("sync op %ld %ld %ld %ld %ld %ld\n", __sync_add_and_fetch(&s, 5), __sync_sub_and_fetch(&s, 3), __sync_or_and_fetch(&s, 0x100), __sync_and_and_fetch(&s, 0x1ff), __sync_xor_and_fetch(&s, 1), __sync_nand_and_fetch(&s, 0xf));
    s = 7;
    printf("sync swap %d %ld %ld\n", __sync_bool_compare_and_swap(&s, 7, 8), __sync_val_compare_and_swap(&s, 8, 9), s);
    int lock = 0;
    int was = __sync_lock_test_and_set(&lock, 1);
    __sync_lock_release(&lock);
    printf("sync lock %d %d\n", was, lock);
    return 0;
}
