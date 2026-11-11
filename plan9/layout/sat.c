#include <u.h>
#include <libc.h>
#include <sat.h>

void
main(void)
{
	print("struct SATParam %d\n", sizeof(struct SATParam));
	print("struct SATParam.errfun %lud\n", offsetof(struct SATParam, errfun));
	print("struct SATParam.erraux %lud\n", offsetof(struct SATParam, erraux));
	print("struct SATParam.randfn %lud\n", offsetof(struct SATParam, randfn));
	print("struct SATParam.randaux %lud\n", offsetof(struct SATParam, randaux));
	print("struct SATParam.goofprob %lud\n", offsetof(struct SATParam, goofprob));
	print("struct SATParam.varρ %lud\n", offsetof(struct SATParam, varρ));
	print("struct SATParam.clauseρ %lud\n", offsetof(struct SATParam, clauseρ));
	print("struct SATParam.trivlim %lud\n", offsetof(struct SATParam, trivlim));
	print("struct SATParam.purgeΔ %lud\n", offsetof(struct SATParam, purgeΔ));
	print("struct SATParam.purgeδ %lud\n", offsetof(struct SATParam, purgeδ));
	print("struct SATParam.purgeα %lud\n", offsetof(struct SATParam, purgeα));
	print("struct SATParam.flushψ %lud\n", offsetof(struct SATParam, flushψ));
	print("struct SATBlock %d\n", sizeof(struct SATBlock));
	print("struct SATBlock.next %lud\n", offsetof(struct SATBlock, next));
	print("struct SATBlock.prev %lud\n", offsetof(struct SATBlock, prev));
	print("struct SATBlock.last %lud\n", offsetof(struct SATBlock, last));
	print("struct SATBlock.end %lud\n", offsetof(struct SATBlock, end));
	print("struct SATBlock.data %lud\n", offsetof(struct SATBlock, data));
	print("struct SATSolve %d\n", sizeof(struct SATSolve));
	print("struct SATSolve.unsat %lud\n", offsetof(struct SATSolve, unsat));
	print("struct SATSolve.scratched %lud\n", offsetof(struct SATSolve, scratched));
	print("struct SATSolve.bl %lud\n", offsetof(struct SATSolve, bl));
	print("struct SATSolve.lastbl %lud\n", offsetof(struct SATSolve, lastbl));
	print("struct SATSolve.cl %lud\n", offsetof(struct SATSolve, cl));
	print("struct SATSolve.learncl %lud\n", offsetof(struct SATSolve, learncl));
	print("struct SATSolve.lastp %lud\n", offsetof(struct SATSolve, lastp));
	print("struct SATSolve.ncl %lud\n", offsetof(struct SATSolve, ncl));
	print("struct SATSolve.ncl0 %lud\n", offsetof(struct SATSolve, ncl0));
	print("struct SATSolve.var %lud\n", offsetof(struct SATSolve, var));
	print("struct SATSolve.lit %lud\n", offsetof(struct SATSolve, lit));
	print("struct SATSolve.nvar %lud\n", offsetof(struct SATSolve, nvar));
	print("struct SATSolve.nvaralloc %lud\n", offsetof(struct SATSolve, nvaralloc));
	print("struct SATSolve.trail %lud\n", offsetof(struct SATSolve, trail));
	print("struct SATSolve.ntrail %lud\n", offsetof(struct SATSolve, ntrail));
	print("struct SATSolve.decbd %lud\n", offsetof(struct SATSolve, decbd));
	print("struct SATSolve.lvl %lud\n", offsetof(struct SATSolve, lvl));
	print("struct SATSolve.heap %lud\n", offsetof(struct SATSolve, heap));
	print("struct SATSolve.nheap %lud\n", offsetof(struct SATSolve, nheap));
	print("struct SATSolve.lvlstamp %lud\n", offsetof(struct SATSolve, lvlstamp));
	print("struct SATSolve.stamp %lud\n", offsetof(struct SATSolve, stamp));
	print("struct SATSolve.forptr %lud\n", offsetof(struct SATSolve, forptr));
	print("struct SATSolve.binptr %lud\n", offsetof(struct SATSolve, binptr));
	print("struct SATSolve.cflcl %lud\n", offsetof(struct SATSolve, cflcl));
	print("struct SATSolve.ncflcl %lud\n", offsetof(struct SATSolve, ncflcl));
	print("struct SATSolve.cflclalloc %lud\n", offsetof(struct SATSolve, cflclalloc));
	print("struct SATSolve.cfllvl %lud\n", offsetof(struct SATSolve, cfllvl));
	print("struct SATSolve.cflctr %lud\n", offsetof(struct SATSolve, cflctr));
	print("struct SATSolve.Δactivity %lud\n", offsetof(struct SATSolve, Δactivity));
	print("struct SATSolve.Δclactivity %lud\n", offsetof(struct SATSolve, Δclactivity));
	print("struct SATSolve.conflicts %lud\n", offsetof(struct SATSolve, conflicts));
	print("struct SATSolve.nextpurge %lud\n", offsetof(struct SATSolve, nextpurge));
	print("struct SATSolve.purgeival %lud\n", offsetof(struct SATSolve, purgeival));
	print("struct SATSolve.fullrcfl %lud\n", offsetof(struct SATSolve, fullrcfl));
	print("struct SATSolve.nfullrcfl %lud\n", offsetof(struct SATSolve, nfullrcfl));
	print("struct SATSolve.fullrlvl %lud\n", offsetof(struct SATSolve, fullrlvl));
	print("struct SATSolve.fullrlits %lud\n", offsetof(struct SATSolve, fullrlits));
	print("struct SATSolve.nfullrlits %lud\n", offsetof(struct SATSolve, nfullrlits));
	print("struct SATSolve.rangecnt %lud\n", offsetof(struct SATSolve, rangecnt));
	print("struct SATSolve.nextflush %lud\n", offsetof(struct SATSolve, nextflush));
	print("struct SATSolve.flushu %lud\n", offsetof(struct SATSolve, flushu));
	print("struct SATSolve.flushv %lud\n", offsetof(struct SATSolve, flushv));
	print("struct SATSolve.flushθ %lud\n", offsetof(struct SATSolve, flushθ));
	print("struct SATSolve.agility %lud\n", offsetof(struct SATSolve, agility));
	print("struct SATSolve.scrap %lud\n", offsetof(struct SATSolve, scrap));
	exits(nil);
}
