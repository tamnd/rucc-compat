//! Doing several cases at once, which is the difference between a sweep somebody runs and a
//! sweep somebody schedules.
//!
//! Every one of the three commands is a map. `differ` preprocesses a case twice and compares,
//! `pipeline` takes a case through rucc three times, and `exec` builds a case four ways and runs
//! it. None of them looks at any case but the one in hand: each gets its own scratch directory
//! named after itself, nothing is written that another one reads, and the compilers are two
//! files on disk that every case only ever executes. So the loop can be several loops.
//!
//! What it deliberately is not is every core. Two reasons, and both of them are about the answer
//! being right rather than about being polite. A case in `exec` is run against a wall clock, and
//! a machine with more work in flight than it can do makes a slow program slower, so a run that
//! took every core would report oversubscription as a timeout and send somebody looking for a
//! performance bug that is not there. And the machines these sweeps run on have a CI runner on
//! them, so a harness that took the whole machine would be measuring itself against a compiler
//! that is being starved.
//!
//! Hence [`jobs`]: half the machine unless told otherwise, and `--jobs 1` still there for when a
//! number is being held against an older one.

use std::sync::Mutex;
use std::sync::atomic::{AtomicUsize, Ordering};
use std::thread;

/// What fraction of the machine a sweep helps itself to when nobody says.
///
/// Two, so half. See the module note for why this is not one.
pub const SHARE: usize = 2;

/// How many cases to have in the air at once.
///
/// `asked` is what the command line said, and `None` is nobody saying. A zero is read as a one,
/// because the alternative is a sweep that does nothing and reports that everything passed.
#[must_use]
pub fn jobs(asked: Option<usize>) -> usize {
    match asked {
        Some(n) => n.max(1),
        None => thread::available_parallelism().map_or(1, |n| n.get() / SHARE).max(1),
    }
}

/// Applies `each` to every item, `jobs` of them at a time, and gives the answers back in the
/// order the items were in.
///
/// The order matters. A report whose rows moved between two runs of the same corpus is a report
/// nobody can diff, and the whole point of the exercise is comparing one run against another.
///
/// One job runs the items on this thread and spawns nothing, so the serial path is a real serial
/// path and not a pool of one. That is what `--jobs 1` is for.
///
/// # Panics
///
/// When `each` panics on some item, since that is a bug in the harness rather than news about a
/// case, and a sweep that swallowed it would report a missing outcome as a passing one.
pub fn spread<T, U, F>(items: &[T], jobs: usize, each: F) -> Vec<U>
where
    T: Sync,
    U: Send,
    F: Fn(&T) -> U + Sync,
{
    if jobs <= 1 || items.len() <= 1 {
        return items.iter().map(each).collect();
    }
    let next = AtomicUsize::new(0);
    let done: Mutex<Vec<(usize, U)>> = Mutex::new(Vec::with_capacity(items.len()));
    thread::scope(|scope| {
        for _ in 0..jobs.min(items.len()) {
            scope.spawn(|| {
                loop {
                    // Handed out one at a time rather than in blocks. The cases are wildly
                    // uneven, a torture case that times out costs ten seconds and one that
                    // refuses to build costs a tenth of that, and a thread that took a block
                    // would sit on the slow half of it while the others had nothing left.
                    let at = next.fetch_add(1, Ordering::Relaxed);
                    let Some(item) = items.get(at) else { return };
                    let answer = each(item);
                    done.lock().expect("no thread panics while holding this").push((at, answer));
                }
            });
        }
    });
    let mut answers = done.into_inner().expect("every thread has finished");
    answers.sort_by_key(|(at, _)| *at);
    answers.into_iter().map(|(_, answer)| answer).collect()
}

#[cfg(test)]
mod tests {
    use std::sync::atomic::AtomicUsize;

    use super::{SHARE, jobs, spread};

    #[test]
    fn a_number_that_was_asked_for_is_the_number() {
        assert_eq!(jobs(Some(4)), 4);
        assert_eq!(jobs(Some(1)), 1);
    }

    #[test]
    fn nothing_at_all_is_still_one_because_none_would_run_nothing() {
        assert_eq!(jobs(Some(0)), 1);
    }

    #[test]
    fn nobody_saying_is_a_share_of_the_machine_and_never_none_of_it() {
        let asked = jobs(None);
        let machine = std::thread::available_parallelism().map_or(1, |n| n.get());
        assert!(asked >= 1, "a sweep with no threads would report that nothing failed");
        assert!(asked <= machine / SHARE || asked == 1);
    }

    #[test]
    fn the_answers_come_back_in_the_order_the_items_were_in() {
        let items: Vec<usize> = (0..200).collect();
        for jobs in [1, 2, 7] {
            let answers = spread(&items, jobs, |n| n * 2);
            assert_eq!(answers, items.iter().map(|n| n * 2).collect::<Vec<_>>());
        }
    }

    #[test]
    fn every_item_is_done_once_and_only_once() {
        let items: Vec<usize> = (0..500).collect();
        let times = AtomicUsize::new(0);
        let answers = spread(&items, 8, |n| {
            times.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
            *n
        });
        assert_eq!(times.into_inner(), 500);
        assert_eq!(answers, items);
    }

    #[test]
    fn nothing_to_do_is_not_an_error() {
        let items: Vec<usize> = Vec::new();
        assert!(spread(&items, 4, |n| *n).is_empty());
    }

    #[test]
    fn one_job_is_a_serial_run_and_not_a_pool_of_one() {
        let items: Vec<usize> = (0..10).collect();
        let here = std::thread::current().id();
        let answers = spread(&items, 1, |_| std::thread::current().id());
        assert!(answers.iter().all(|id| *id == here));
    }
}
