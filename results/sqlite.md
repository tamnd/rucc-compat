# sqlite

sqlite: 4 cases, 2 same, 0 unsupported, 2 accepted, 0 failing

Reference: `cc`. Under test: `/Users/apple/github/tamnd/rucc/target/release/rucc`. Markers compared: no.

Nothing failing.

## Accepted

Differences the register covers, each waiting on the issue it names.

### darwin-availability

A declaration in an Apple system header comes out without its availability attribute. Apple's AvailabilityInternal.h defines the whole family behind __has_attribute(availability), which we answer no to because the attribute is not implemented, and answering no is the matrix working as intended: a header that asks gets the fallback path rather than syntax we cannot parse. Waiting on https://github.com/tamnd/rucc/issues/31.

- amalgamation/sqlite3.c (tokens)
- shell/shell.c (tokens)

