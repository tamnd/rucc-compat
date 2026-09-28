/* The atomic builtins, both the __atomic family and the older __sync one, which Postgres's
 * port/atomics headers pick between. One thread, so this is about the values each one answers and
 * leaves behind rather than about ordering. */
#include <stdint.h>
#include "../check.h"

#if __has_builtin(__atomic_load_n)
#define HAS_0 1
#else
#define HAS_0 0
#endif
#if __has_builtin(__atomic_store_n)
#define HAS_1 1
#else
#define HAS_1 0
#endif
#if __has_builtin(__atomic_exchange_n)
#define HAS_2 1
#else
#define HAS_2 0
#endif
#if __has_builtin(__atomic_compare_exchange_n)
#define HAS_3 1
#else
#define HAS_3 0
#endif
#if __has_builtin(__atomic_fetch_add)
#define HAS_4 1
#else
#define HAS_4 0
#endif
#if __has_builtin(__atomic_fetch_sub)
#define HAS_5 1
#else
#define HAS_5 0
#endif
#if __has_builtin(__atomic_fetch_and)
#define HAS_6 1
#else
#define HAS_6 0
#endif
#if __has_builtin(__atomic_fetch_or)
#define HAS_7 1
#else
#define HAS_7 0
#endif
#if __has_builtin(__atomic_add_fetch)
#define HAS_8 1
#else
#define HAS_8 0
#endif
#if __has_builtin(__atomic_test_and_set)
#define HAS_9 1
#else
#define HAS_9 0
#endif
#if __has_builtin(__atomic_clear)
#define HAS_10 1
#else
#define HAS_10 0
#endif
#if __has_builtin(__atomic_thread_fence)
#define HAS_11 1
#else
#define HAS_11 0
#endif
#if __has_builtin(__atomic_always_lock_free)
#define HAS_12 1
#else
#define HAS_12 0
#endif
#if __has_builtin(__sync_fetch_and_add)
#define HAS_13 1
#else
#define HAS_13 0
#endif
#if __has_builtin(__sync_fetch_and_or)
#define HAS_14 1
#else
#define HAS_14 0
#endif
#if __has_builtin(__sync_bool_compare_and_swap)
#define HAS_15 1
#else
#define HAS_15 0
#endif
#if __has_builtin(__sync_val_compare_and_swap)
#define HAS_16 1
#else
#define HAS_16 0
#endif
#if __has_builtin(__sync_lock_test_and_set)
#define HAS_17 1
#else
#define HAS_17 0
#endif
#if __has_builtin(__sync_lock_release)
#define HAS_18 1
#else
#define HAS_18 0
#endif
#if __has_builtin(__sync_synchronize)
#define HAS_19 1
#else
#define HAS_19 0
#endif

int main(void) {
    CLAIM("__has_builtin(__atomic_load_n)", HAS_0);
    CLAIM("__has_builtin(__atomic_store_n)", HAS_1);
    CLAIM("__has_builtin(__atomic_exchange_n)", HAS_2);
    CLAIM("__has_builtin(__atomic_compare_exchange_n)", HAS_3);
    CLAIM("__has_builtin(__atomic_fetch_add)", HAS_4);
    CLAIM("__has_builtin(__atomic_fetch_sub)", HAS_5);
    CLAIM("__has_builtin(__atomic_fetch_and)", HAS_6);
    CLAIM("__has_builtin(__atomic_fetch_or)", HAS_7);
    CLAIM("__has_builtin(__atomic_add_fetch)", HAS_8);
    CLAIM("__has_builtin(__atomic_test_and_set)", HAS_9);
    CLAIM("__has_builtin(__atomic_clear)", HAS_10);
    CLAIM("__has_builtin(__atomic_thread_fence)", HAS_11);
    CLAIM("__has_builtin(__atomic_always_lock_free)", HAS_12);
    CLAIM("__has_builtin(__sync_fetch_and_add)", HAS_13);
    CLAIM("__has_builtin(__sync_fetch_and_or)", HAS_14);
    CLAIM("__has_builtin(__sync_bool_compare_and_swap)", HAS_15);
    CLAIM("__has_builtin(__sync_val_compare_and_swap)", HAS_16);
    CLAIM("__has_builtin(__sync_lock_test_and_set)", HAS_17);
    CLAIM("__has_builtin(__sync_lock_release)", HAS_18);
    CLAIM("__has_builtin(__sync_synchronize)", HAS_19);
    int v = 5;
    long long w = 1;
    unsigned char flag = 0;
    CHECK(__atomic_load_n(&v, __ATOMIC_SEQ_CST) == 5);
    __atomic_store_n(&v, 6, __ATOMIC_RELEASE);
    CHECK(v == 6);
    CHECK(__atomic_exchange_n(&v, 7, __ATOMIC_ACQ_REL) == 6 && v == 7);
    int expected = 7;
    CHECK(__atomic_compare_exchange_n(&v, &expected, 8, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST) && v == 8);
    expected = 1;
    CHECK(!__atomic_compare_exchange_n(&v, &expected, 9, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST) && expected == 8);
    CHECK(__atomic_fetch_add(&v, 2, __ATOMIC_RELAXED) == 8 && v == 10);
    CHECK(__atomic_fetch_sub(&v, 3, __ATOMIC_RELAXED) == 10 && v == 7);
    CHECK(__atomic_fetch_and(&v, 3, __ATOMIC_RELAXED) == 7 && v == 3);
    CHECK(__atomic_fetch_or(&v, 12, __ATOMIC_RELAXED) == 3 && v == 15);
    CHECK(__atomic_add_fetch(&w, 1LL << 40, __ATOMIC_SEQ_CST) == (1LL << 40) + 1);
    CHECK(!__atomic_test_and_set(&flag, __ATOMIC_ACQUIRE) && __atomic_test_and_set(&flag, __ATOMIC_ACQUIRE));
    __atomic_clear(&flag, __ATOMIC_RELEASE);
    CHECK(!__atomic_test_and_set(&flag, __ATOMIC_ACQUIRE));
    __atomic_thread_fence(__ATOMIC_SEQ_CST);
    CHECK(__atomic_always_lock_free(sizeof(long), 0));
    uint32_t u = 1;
    CHECK(__sync_fetch_and_add(&u, 4) == 1 && u == 5);
    CHECK(__sync_fetch_and_or(&u, 8) == 5 && u == 13);
    CHECK(__sync_bool_compare_and_swap(&u, 13, 20) && u == 20);
    CHECK(!__sync_bool_compare_and_swap(&u, 13, 21) && u == 20);
    CHECK(__sync_val_compare_and_swap(&u, 20, 30) == 20 && u == 30);
    int lock = 0;
    CHECK(__sync_lock_test_and_set(&lock, 1) == 0 && lock == 1);
    __sync_lock_release(&lock);
    CHECK(lock == 0);
    __sync_synchronize();
    DONE();
}
