# Results

Reports written by `rucc-compat run --report`, one markdown file per corpus.

A result is about the machine that produced it: which libc is installed, which compiler `cc` turned out to be, and which build of rucc was under test. That is in the header of every report, and it is why CI keeps its own reports as build artifacts rather than committing them over each other.

Commit a report here when it is worth pointing at, such as the first clean sweep of a header set or the run that a divergence entry refers to.
