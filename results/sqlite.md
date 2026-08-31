# sqlite

sqlite: 1 cases, 0 same, 0 unsupported, 0 accepted, 1 failing

Reference: `cc`. Under test: `/Users/apple/github/tamnd/rucc/target/release/rucc`. Markers compared: no.

## Failing

### shell/shell.c (tokens)

Line 588 of the normalized output.

```
rucc: int getiopolicy_np(int, int);
cc:   int getiopolicy_np(int, int) __attribute__((availability(macosx,introduced=10.5)));
```

