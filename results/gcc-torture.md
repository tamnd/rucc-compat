# gcc-torture

gcc-torture: 1772 cases, 1592 same, 0 unsupported, 80 accepted, 100 failing

Reference: `cc`. Under test: `/Users/apple/github/tamnd/rucc/target/release/rucc`. Markers compared: no.

## Failing

### execute/20010329-1.c (tokens)

Line 5 of the normalized output.

```
rucc: void *x = ((void *)((unsigned int)0x7fffffff + 2));
cc:   void *x = ((void *)((unsigned int)2147483647 + 2));
```

### execute/20020506-1.c (tokens)

Line 13 of the normalized output.

```
rucc: if ((c & (0x7f +1)) == 0)
cc:   if ((c & (127 +1)) == 0)
```

### execute/20020510-1.c (tokens)

Line 5 of the normalized output.

```
rucc: if ((c>=1) && (c<=0x7f))
cc:   if ((c>=1) && (c<=127))
```

### execute/20020614-1.c (tokens)

Line 8 of the normalized output.

```
rucc: i = 0x7f;
cc:   i = 127;
```

### execute/20021010-1.c (tokens)

Line 7 of the normalized output.

```
rucc: if (a / 0x7fffffff / 16 == 0)
cc:   if (a / 2147483647 / 16 == 0)
```

### execute/20021120-1.c (spacing)

Line 7 of the normalized output.

```
rucc: double d00, d10, d20, d30, d01, d11, d21, d31, d02, d12, d22, d32, d03, d13, d23, d33, d04, d14, d24, d34, d05, d15, d25, d35, d06, d16, d26, d36, d07, d17, d27, d37;
cc:   double d00 , d10 , d20 , d30 , d01 , d11 , d21 , d31 , d02 , d12 , d22 , d32 , d03 , d13 , d23 , d33 , d04 , d14 , d24 , d34 , d05 , d15 , d25 , d35 , d06 , d16 , d26 , d36 , d07 , d17 , d27 , d37 ;
```

### execute/20030222-1.c (tokens)

Line 10 of the normalized output.

```
rucc: int val = (-0x7fffffff -1) + 1;
cc:   int val = (-2147483647 -1) + 1;
```

### execute/20030403-1.c (tokens)

Line 6 of the normalized output.

```
rucc: if (count > 0x7fffffff)
cc:   if (count > 2147483647)
```

### execute/20031020-1.c (tokens)

Line 11 of the normalized output.

```
rucc: foo ((-0x7fffffffffffffffL -1L));
cc:   foo ((-9223372036854775807L -1L));
```

### execute/20040409-1.c (tokens)

Line 4 of the normalized output.

```
rucc: return x ^ (-0x7fffffff -1);
cc:   return x ^ (-2147483647 -1);
```

### execute/20040409-1w.c (tokens)

Line 4 of the normalized output.

```
rucc: return x + (-0x7fffffff -1);
cc:   return x + (-2147483647 -1);
```

### execute/20040409-2.c (tokens)

Line 4 of the normalized output.

```
rucc: return (x ^ (-0x7fffffff -1)) ^ 0x1234;
cc:   return (x ^ (-2147483647 -1)) ^ 0x1234;
```

### execute/20040409-2w.c (tokens)

Line 4 of the normalized output.

```
rucc: return (x + (-0x7fffffff -1)) ^ 0x1234;
cc:   return (x + (-2147483647 -1)) ^ 0x1234;
```

### execute/20040409-3.c (tokens)

Line 4 of the normalized output.

```
rucc: return ~(x ^ (-0x7fffffff -1));
cc:   return ~(x ^ (-2147483647 -1));
```

### execute/20040409-3w.c (tokens)

Line 4 of the normalized output.

```
rucc: return ~(x + (-0x7fffffff -1));
cc:   return ~(x + (-2147483647 -1));
```

### execute/20040629-1.c (tokens)

Line 36 of the normalized output.

```
rucc: return 0;
cc:   b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_1 (3); if (ret1 () != ((51 + 3) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_1 (251); if (ret2 () != ((636 + 251) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_1 (13279); if (ret3 () != ((31278 + 13279) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_1 (24); if (ret4 () != ((21 + 24) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_1 (1); if (ret5 () != ((1 + 1) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_1 (264151); if (ret6 () != ((33554432 + 264151) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_1 (713); if (ret7 () != ((26812 + 713) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_1 (17); if (ret8 () != ((156 + 17) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_1 (199); if (ret9 () != ((187 + 199) & ((1 << 8) - 1))) abort (); d.k = 187;
```

### execute/20040705-1.c (tokens)

Line 36 of the normalized output.

```
rucc: return 0;
cc:   b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_1 (3); if (ret1 () != ((51 + 3) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_1 (251); if (ret2 () != ((636 + 251) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_1 (13279); if (ret3 () != ((31278 + 13279) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_1 (24); if (ret4 () != ((21 + 24) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_1 (1); if (ret5 () != ((1 + 1) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_1 (264151); if (ret6 () != ((33554432 + 264151) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_1 (713); if (ret7 () != ((26812 + 713) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_1 (17); if (ret8 () != ((156 + 17) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_1 (199); if (ret9 () != ((187 + 199) & ((1 << 8) - 1))) abort (); d.k = 187;
```

### execute/20040705-2.c (tokens)

Line 36 of the normalized output.

```
rucc: return 0;
cc:   b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_1 (3); if (ret1 () != ((51 + 3) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_1 (251); if (ret2 () != ((636 + 251) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_1 (13279); if (ret3 () != ((31278 + 13279) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_1 (24); if (ret4 () != ((21 + 24) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_1 (1); if (ret5 () != ((1 + 1) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_1 (264151); if (ret6 () != ((33554432 + 264151) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_1 (713); if (ret7 () != ((26812 + 713) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_1 (17); if (ret8 () != ((156 + 17) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_1 (199); if (ret9 () != ((187 + 199) & ((1 << 8) - 1))) abort (); d.k = 187;
```

### execute/20041114-1.c (tokens)

Line 8 of the normalized output.

```
rucc: || ((long unsigned) (unsigned) (var - 1) < (0x7fffffff *2U +1U))))
cc:   || ((long unsigned) (unsigned) (var - 1) < (2147483647 *2U +1U))))
```

### execute/20041210-1.c (tokens)

Line 3 of the normalized output.

```
rucc: int x[4] = { (-0x7fffffff -1) / 2, 0x7fffffff, 2, 4 };
cc:   int x[4] = { (-2147483647 -1) / 2, 2147483647, 2, 4 };
```

### execute/20050104-1.c (tokens)

Line 5 of the normalized output.

```
rucc: return -0x7fffffffffffffffLL - 1;
cc:   return -9223372036854775807LL - 1;
```

### execute/20070623-1.c (tokens)

Line 15 of the normalized output.

```
rucc: if (nge((-0x7fffffff -1), 0x7fffffff) != 0) abort();
cc:   if (nge((-2147483647 -1), 2147483647) != 0) abort();
```

### execute/20081112-1.c (tokens)

Line 4 of the normalized output.

```
rucc: int b = (a - 1) + (-0x7fffffff -1);
cc:   int b = (a - 1) + (-2147483647 -1);
```

### execute/20111208-1.c (tokens)

Line 7 of the normalized output.

```
rucc: typedef short int int16_t;
cc:   typedef short int16_t;
```

### execute/980709-1.c (tokens)

Line 7 of the normalized output.

```
rucc: extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isfinitef(float);
cc:   inline __attribute__ ((__always_inline__)) int __inline_isfinitef(float);
```

### execute/builtin-bitops-1.c (tokens)

Line 1 of the normalized output.

```
rucc: void __assert_rtn(const char *, const char *, int, const char *) __attribute__((__noreturn__)) ;
cc:   void __assert_rtn(const char *, const char *, int, const char *) __attribute__((__noreturn__)) __attribute__((__cold__)) __attribute__((__disable_tail_calls__));
```

### execute/builtins/abs-2.c (tokens)

Line 11 of the normalized output.

```
rucc: volatile int i0 = 0, i1 = 1, im1 = -1, imin = -0x7fffffff, imax = 0x7fffffff;
cc:   volatile int i0 = 0, i1 = 1, im1 = -1, imin = -2147483647, imax = 2147483647;
```

### execute/builtins/abs-3.c (tokens)

Line 7 of the normalized output.

```
rucc: volatile int i0 = 0, i1 = 1, im1 = -1, imin = -0x7fffffff, imax = 0x7fffffff;
cc:   volatile int i0 = 0, i1 = 1, im1 = -1, imin = -2147483647, imax = 2147483647;
```

### execute/builtins/lib/chk.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/memcpy-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/memmove-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/mempcpy-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/memset-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/pr23484-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/pr93262-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/snprintf-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/sprintf-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/stpcpy-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/stpncpy-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/strcat-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/strcat-chk.c (spacing)

Line 64 of the normalized output.

```
rucc: __builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), "a ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), 0)), "test", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), "a ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), 0)), 0)), ".", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), "a ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), 0)), "test", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), "a ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), 0)), 0)), 0))
cc:   __builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), "a ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), 0)), "test", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), "a ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), 0)), 0)), ".", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), "a ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), 0)), "test", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), "a ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), 0)), 0)), 0));
```

### execute/builtins/strcpy-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/strncat-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/strncpy-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/strnlen.c (tokens)

Line 9 of the normalized output.

```
rucc: ((strnlen ("", 0x7fffffffffffffffL) == 0) ? (void)0 : (__builtin_printf ("assertion on line %i failed: %s\n", 24, "strnlen (\"\", PTRDIFF_MAX) == 0"), abort ()));
cc:   ((strnlen ("", 9223372036854775807L) == 0) ? (void)0 : (__builtin_printf ("assertion on line %i failed: %s\n", 24, "strnlen (\"\", PTRDIFF_MAX) == 0"), abort ()));
```

### execute/builtins/uabs-2.c (tokens)

Line 12 of the normalized output.

```
rucc: volatile int i0 = 0, i1 = 1, im1 = -1, imin = -0x7fffffff, imax = 0x7fffffff;
cc:   volatile int i0 = 0, i1 = 1, im1 = -1, imin = -2147483647, imax = 2147483647;
```

### execute/builtins/uabs-3.c (tokens)

Line 8 of the normalized output.

```
rucc: volatile int i0 = 0, i1 = 1, im1 = -1, imin = -0x7fffffff, imax = 0x7fffffff;
cc:   volatile int i0 = 0, i1 = 1, im1 = -1, imin = -2147483647, imax = 2147483647;
```

### execute/builtins/vsnprintf-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/builtins/vsprintf-chk-lib.c (tokens)

Line 3 of the normalized output.

```
rucc: typedef signed char __int8_t;
cc:   extern void abort (void);
```

### execute/doloop-1.c (tokens)

Line 10 of the normalized output.

```
rucc: if (i != (0x7f*2 +1) + 1U)
cc:   if (i != (127*2 +1) + 1U)
```

### execute/doloop-2.c (tokens)

Line 10 of the normalized output.

```
rucc: if (i != (0x7fff * 2 + 1) + 1U)
cc:   if (i != (32767 * 2 + 1) + 1U)
```

### execute/ieee/20010226-1.c (tokens)

Line 8 of the normalized output.

```
rucc: if (2.22044604925031308084726333618164062e-16L > 0x1p-31L)
cc:   if (2.2204460492503131e-16L > 0x1p-31L)
```

### execute/ieee/acc2.c (tokens)

Line 13 of the normalized output.

```
rucc: double values[] = { ((double)1.79769313486231570814527423731704357e+308L), 2.0, 0.5, 1.0 };
cc:   double values[] = { 1.7976931348623157e+308, 2.0, 0.5, 1.0 };
```

### execute/ieee/cdivchkd.c (tokens)

Line 14 of the normalized output.

```
rucc: if (__builtin_fabs (rz) > ((double)2.22507385850720138309023271733240406e-308L))
cc:   if (__builtin_fabs (rz) > 2.2250738585072014e-308)
```

### execute/ieee/cdivchkf.c (tokens)

Line 15 of the normalized output.

```
rucc: if (__builtin_fabsf (rz) > 1.17549435082228750796873653722224568e-38F)
cc:   if (__builtin_fabsf (rz) > 1.17549435e-38F)
```

### execute/ieee/cdivchkld.c (tokens)

Line 14 of the normalized output.

```
rucc: if (__builtin_fabsl (rz) > 2.22507385850720138309023271733240406e-308L)
cc:   if (__builtin_fabsl (rz) > 2.2250738585072014e-308L)
```

### execute/ieee/fp-cmp-1.c (tokens)

Line 316 of the normalized output.

```
rucc: void (* bsd_signal(int, void (* )(int)))(int);
cc:   void (* _Nullable bsd_signal(int, void (* _Nullable)(int)))(int);
```

### execute/ieee/fp-cmp-2.c (tokens)

Line 316 of the normalized output.

```
rucc: void (* bsd_signal(int, void (* )(int)))(int);
cc:   void (* _Nullable bsd_signal(int, void (* _Nullable)(int)))(int);
```

### execute/ieee/fp-cmp-3.c (tokens)

Line 316 of the normalized output.

```
rucc: void (* bsd_signal(int, void (* )(int)))(int);
cc:   void (* _Nullable bsd_signal(int, void (* _Nullable)(int)))(int);
```

### execute/ieee/hugeval.c (tokens)

Line 7 of the normalized output.

```
rucc: extern __inline __attribute__((__gnu_inline__)) __attribute__ ((__always_inline__)) int __inline_isfinitef(float);
cc:   inline __attribute__ ((__always_inline__)) int __inline_isfinitef(float);
```

### execute/ieee/pr108540-1.c (tokens)

Line 41 of the normalized output.

```
rucc: union U { long int l; double d; } u;
cc:   union U { long long int l; double d; } u;
```

### execute/ieee/pr109008.c (tokens)

Line 12 of the normalized output.

```
rucc: if (foo (((double)2.22044604925031308084726333618164062e-16L) / 8.0) == 0.0)
cc:   if (foo (2.2204460492503131e-16 / 8.0) == 0.0)
```

### execute/ieee/pr36332.c (tokens)

Line 9 of the normalized output.

```
rucc: if (foo (1.79769313486231570814527423731704357e+308L))
cc:   if (foo (1.7976931348623157e+308L))
```

### execute/ieee/unsafe-fp-assoc.c (tokens)

Line 2 of the normalized output.

```
rucc: static const double C = ((double)1.79769313486231570814527423731704357e+308L);
cc:   static const double C = 1.7976931348623157e+308;
```

### execute/loop-2b.c (tokens)

Line 7 of the normalized output.

```
rucc: for (; i < 0x7fffffff; i++)
cc:   for (; i < 2147483647; i++)
```

### execute/loop-2e.c (tokens)

Line 16 of the normalized output.

```
rucc: start = (long unsigned int) 0x7fffffff;
cc:   start = (long unsigned int) 2147483647;
```

### execute/loop-2f.c (tokens)

Line 132 of the normalized output.

```
rucc: _data = (((_data ^ (_data >> 16 | (_data << 16))) & 0xFF00FFFF) >> 8) ^ (_data >> 8 | _data << 24);
cc:   _data = __builtin_bswap32(_data);
```

### execute/loop-2g.c (tokens)

Line 132 of the normalized output.

```
rucc: _data = (((_data ^ (_data >> 16 | (_data << 16))) & 0xFF00FFFF) >> 8) ^ (_data >> 8 | _data << 24);
cc:   _data = __builtin_bswap32(_data);
```

### execute/mul-sext.c (tokens)

Line 1 of the normalized output.

```
rucc: typedef long int int64_t;
cc:   typedef long long int int64_t;
```

### execute/pr101188.c (tokens)

Line 2 of the normalized output.

```
rucc: typedef short unsigned int uint16_t;
cc:   typedef unsigned short uint16_t;
```

### execute/pr104196.c (tokens)

Line 7 of the normalized output.

```
rucc: int b = a < 0 && 0 < -0x7fffffff - a ? 0 : a;
cc:   int b = a < 0 && 0 < -2147483647 - a ? 0 : a;
```

### execute/pr108789.c (tokens)

Line 15 of the normalized output.

```
rucc: x = (0x7fffffff + 1U) / 2;
cc:   x = (2147483647 + 1U) / 2;
```

### execute/pr111151.c (tokens)

Line 4 of the normalized output.

```
rucc: unsigned a = (1U + 0x7fffffff) / 2U;
cc:   unsigned a = (1U + 2147483647) / 2U;
```

### execute/pr112758.c (tokens)

Line 1 of the normalized output.

```
rucc: int a = -0x7fffffff - 1;
cc:   int a = -2147483647 - 1;
```

### execute/pr122943.c (tokens)

Line 66 of the normalized output.

```
rucc: if (foo (-0x7fffffffffffffffLL - 1) != 0)
cc:   if (foo (-9223372036854775807LL - 1) != 0)
```

### execute/pr123864.c (tokens)

Line 11 of the normalized output.

```
rucc: if (foo (0x7fffffff + 1LL))
cc:   if (foo (2147483647 + 1LL))
```

### execute/pr22493-1.c (tokens)

Line 14 of the normalized output.

```
rucc: f((-0x7fffffff -1));
cc:   f((-2147483647 -1));
```

### execute/pr23047.c (tokens)

Line 12 of the normalized output.

```
rucc: f((-0x7fffffff -1));
cc:   f((-2147483647 -1));
```

### execute/pr23941.c (tokens)

Line 2 of the normalized output.

```
rucc: double d = 1.17549435082228750796873653722224568e-38F / 2.0;
cc:   double d = 1.17549435e-38F / 2.0;
```

### execute/pr28651.c (tokens)

Line 10 of the normalized output.

```
rucc: unsigned int u = 0x7fffffff;
cc:   unsigned int u = 2147483647;
```

### execute/pr39228.c (tokens)

Line 19 of the normalized output.

```
rucc: if (testf (3.40282346638528859811704183484516925e+38F) < 1)
cc:   if (testf (3.40282347e+38F) < 1)
```

### execute/pr40579.c (tokens)

Line 15 of the normalized output.

```
rucc: int x = -0x7fffffff + 3;
cc:   int x = -2147483647 + 3;
```

### execute/pr50865.c (tokens)

Line 7 of the normalized output.

```
rucc: if (((-0x7fffffffffffffffLL - 1) % 1LL) != 0)
cc:   if (((-9223372036854775807LL - 1) % 1LL) != 0)
```

### execute/pr51581-1.c (tokens)

Line 101 of the normalized output.

```
rucc: a[0] = -0x7fffffff - 1;
cc:   a[0] = -2147483647 - 1;
```

### execute/pr51581-2.c (tokens)

Line 117 of the normalized output.

```
rucc: a[0] = -0x7fffffff - 1;
cc:   a[0] = -2147483647 - 1;
```

### execute/pr55137.c (tokens)

Line 20 of the normalized output.

```
rucc: if (foo (0x7fffffff) != (bar (0x7fffffff) < 0x7fffffff)
cc:   if (foo (2147483647) != (bar (2147483647) < 2147483647)
```

### execute/pr58831.c (tokens)

Line 1 of the normalized output.

```
rucc: void __assert_rtn(const char *, const char *, int, const char *) __attribute__((__noreturn__)) ;
cc:   void __assert_rtn(const char *, const char *, int, const char *) __attribute__((__noreturn__)) __attribute__((__cold__)) __attribute__((__disable_tail_calls__));
```

### execute/pr61306-2.c (tokens)

Line 1 of the normalized output.

```
rucc: typedef short int int16_t;
cc:   typedef short int16_t;
```

### execute/pr61375.c (tokens)

Line 1 of the normalized output.

```
rucc: typedef long unsigned int uint64_t;
cc:   typedef long long unsigned int uint64_t;
```

### execute/pr69097-2.c (tokens)

Line 20 of the normalized output.

```
rucc: if (f1 (-0x7fffffff - 1, 1) != 0
cc:   if (f1 (-2147483647 - 1, 1) != 0
```

### execute/pr71554.c (tokens)

Line 11 of the normalized output.

```
rucc: signed int y = ((-0x7fffffff - 1) / 2);
cc:   signed int y = ((-2147483647 - 1) / 2);
```

### execute/pr78622.c (tokens)

Line 14 of the normalized output.

```
rucc: if (0x7f != 127 || 8 != 8 || 4 != 4)
cc:   if (127 != 127 || 8 != 8 || 4 != 4)
```

### execute/pr81281.c (tokens)

Line 5 of the normalized output.

```
rucc: if (a - (1U + 0x7fffffff) >= 2)
cc:   if (a - (1U + 2147483647) >= 2)
```

### execute/pr82192.c (tokens)

Line 12 of the normalized output.

```
rucc: if (0x7fffffff != 0x7fffffffULL)
cc:   if (2147483647 != 0x7fffffffULL)
```

### execute/pr89634.c (tokens)

Line 32 of the normalized output.

```
rucc: unsigned long a[18] = { 4, 2, -200, 200, 2, -400, 400, 3, -600, 0, 600, 5, -100, -66, 0, 66, 100, 0x7fffffffffffffffL / 8 + 1 };
cc:   unsigned long a[18] = { 4, 2, -200, 200, 2, -400, 400, 3, -600, 0, 600, 5, -100, -66, 0, 66, 100, 9223372036854775807L / 8 + 1 };
```

### execute/pr93213.c (tokens)

Line 1 of the normalized output.

```
rucc: typedef unsigned short int u16;
cc:   typedef unsigned short u16;
```

### execute/pr94412.c (tokens)

Line 16 of the normalized output.

```
rucc: V b = (V) { 3, 0x7fffffff };
cc:   V b = (V) { 3, 2147483647 };
```

### execute/pr98727.c (tokens)

Line 14 of the normalized output.

```
rucc: || foo (0x7fffffffffffffffL / 16, 17) != -1)
cc:   || foo (9223372036854775807L / 16, 17) != -1)
```

### execute/stkalign.c (tokens)

Line 1 of the normalized output.

```
rucc: void __assert_rtn(const char *, const char *, int, const char *) __attribute__((__noreturn__)) ;
cc:   void __assert_rtn(const char *, const char *, int, const char *) __attribute__((__noreturn__)) __attribute__((__cold__)) __attribute__((__disable_tail_calls__));
```

### execute/vrp-6.c (tokens)

Line 16 of the normalized output.

```
rucc: if (a - b < (0x7fffffff *2U +1U) - 15U)
cc:   if (a - b < (2147483647 *2U +1U) - 15U)
```

## Accepted

Differences the register covers, each waiting on the issue it names.

### darwin-availability

A declaration in an Apple system header comes out without its availability attribute. Apple's AvailabilityInternal.h defines the whole family behind __has_attribute(availability), which we answer no to because the attribute is not implemented, and answering no is the matrix working as intended: a header that asks gets the fallback path rather than syntax we cannot parse. Waiting on https://github.com/tamnd/rucc/issues/31.

- execute/20000112-1.c (tokens)
- execute/20000402-1.c (tokens)
- execute/20000910-1.c (tokens)
- execute/20000910-2.c (tokens)
- execute/20021010-2.c (tokens)
- execute/20031204-1.c (tokens)
- execute/20040823-1.c (tokens)
- execute/20050125-1.c (tokens)
- execute/20050131-1.c (tokens)
- execute/20050203-1.c (tokens)
- execute/20120111-1.c (tokens)
- execute/20221006-1.c (tokens)
- execute/920501-6.c (tokens)
- execute/920501-8.c (tokens)
- execute/920726-1.c (tokens)
- execute/920810-1.c (tokens)
- execute/941014-2.c (tokens)
- execute/960311-1.c (tokens)
- execute/960311-2.c (tokens)
- execute/960311-3.c (tokens)
- execute/960327-1.c (tokens)
- execute/960521-1.c (tokens)
- execute/980605-1.c (tokens)
- execute/980707-1.c (tokens)
- execute/990513-1.c (tokens)
- execute/990628-1.c (tokens)
- execute/990826-0.c (tokens)
- execute/builtins/fprintf-lib.c (tokens)
- execute/builtins/fprintf.c (tokens)
- execute/builtins/fputs-lib.c (tokens)
- execute/builtins/fputs.c (tokens)
- execute/builtins/lib/fprintf.c (tokens)
- execute/builtins/lib/printf.c (tokens)
- execute/builtins/lib/sprintf.c (tokens)
- execute/builtins/printf-lib.c (tokens)
- execute/builtins/sprintf-lib.c (tokens)
- execute/comp-goto-1.c (tokens)
- execute/complex-6.c (tokens)
- execute/const-addr-expr-1.c (tokens)
- execute/enum-3.c (tokens)
- execute/fprintf-1.c (tokens)
- execute/fprintf-2.c (tokens)
- execute/fprintf-chk-1.c (tokens)
- execute/gofast.c (tokens)
- execute/ieee/920810-1.c (tokens)
- execute/ieee/copysign1.c (tokens)
- execute/ieee/copysign2.c (tokens)
- execute/memcpy-1.c (tokens)
- execute/memcpy-2.c (tokens)
- execute/memcpy-bi.c (tokens)
- execute/memset-1.c (tokens)
- execute/memset-2.c (tokens)
- execute/memset-3.c (tokens)
- execute/mode-dependent-address.c (tokens)
- execute/p18298.c (tokens)
- execute/pr103209.c (tokens)
- execute/pr111613.c (tokens)
- execute/pr114207.c (tokens)
- execute/pr34456.c (tokens)
- execute/pr41463.c (tokens)
- execute/pr56799.c (tokens)
- execute/pr69320-1.c (tokens)
- execute/pr69320-2.c (tokens)
- execute/pr69320-3.c (tokens)
- execute/pr69320-4.c (tokens)
- execute/printf-1.c (tokens)
- execute/printf-2.c (tokens)
- execute/printf-chk-1.c (tokens)
- execute/strcmp-1.c (tokens)
- execute/strcpy-1.c (tokens)
- execute/strlen-1.c (tokens)
- execute/strncmp-1.c (tokens)
- execute/struct-ret-1.c (tokens)
- execute/user-printf.c (tokens)
- execute/va-arg-21.c (tokens)
- execute/va-arg-24.c (tokens)
- execute/vfprintf-1.c (tokens)
- execute/vfprintf-chk-1.c (tokens)
- execute/vprintf-1.c (tokens)
- execute/vprintf-chk-1.c (tokens)

