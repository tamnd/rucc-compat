#include <u.h>
#include <libc.h>
#include <draw.h>
#include <mouse.h>
#include <control.h>

void
main(void)
{
	print("struct Controlset %d\n", sizeof(struct Controlset));
	print("struct Controlset.controls %lud\n", offsetof(struct Controlset, controls));
	print("struct Controlset.screen %lud\n", offsetof(struct Controlset, screen));
	print("struct Controlset.actives %lud\n", offsetof(struct Controlset, actives));
	print("struct Controlset.focus %lud\n", offsetof(struct Controlset, focus));
	print("struct Controlset.ctl %lud\n", offsetof(struct Controlset, ctl));
	print("struct Controlset.data %lud\n", offsetof(struct Controlset, data));
	print("struct Controlset.kbdc %lud\n", offsetof(struct Controlset, kbdc));
	print("struct Controlset.mousec %lud\n", offsetof(struct Controlset, mousec));
	print("struct Controlset.resizec %lud\n", offsetof(struct Controlset, resizec));
	print("struct Controlset.resizeexitc %lud\n", offsetof(struct Controlset, resizeexitc));
	print("struct Controlset.csexitc %lud\n", offsetof(struct Controlset, csexitc));
	print("struct Controlset.keyboardctl %lud\n", offsetof(struct Controlset, keyboardctl));
	print("struct Controlset.mousectl %lud\n", offsetof(struct Controlset, mousectl));
	print("struct Controlset.clicktotype %lud\n", offsetof(struct Controlset, clicktotype));
	print("struct Control %d\n", sizeof(struct Control));
	print("struct Control.name %lud\n", offsetof(struct Control, name));
	print("struct Control.rect %lud\n", offsetof(struct Control, rect));
	print("struct Control.size %lud\n", offsetof(struct Control, size));
	print("struct Control.event %lud\n", offsetof(struct Control, event));
	print("struct Control.data %lud\n", offsetof(struct Control, data));
	print("struct Control.type %lud\n", offsetof(struct Control, type));
	print("struct Control.hidden %lud\n", offsetof(struct Control, hidden));
	print("struct Control.controlset %lud\n", offsetof(struct Control, controlset));
	print("struct Control.screen %lud\n", offsetof(struct Control, screen));
	print("struct Control.format %lud\n", offsetof(struct Control, format));
	print("struct Control.wevent %lud\n", offsetof(struct Control, wevent));
	print("struct Control.wdata %lud\n", offsetof(struct Control, wdata));
	print("struct Control.ctl %lud\n", offsetof(struct Control, ctl));
	print("struct Control.mouse %lud\n", offsetof(struct Control, mouse));
	print("struct Control.key %lud\n", offsetof(struct Control, key));
	print("struct Control.exit %lud\n", offsetof(struct Control, exit));
	print("struct Control.setsize %lud\n", offsetof(struct Control, setsize));
	print("struct Control.activate %lud\n", offsetof(struct Control, activate));
	print("struct Control.nextactive %lud\n", offsetof(struct Control, nextactive));
	print("struct Control.next %lud\n", offsetof(struct Control, next));
	print("struct CCache %d\n", sizeof(struct CCache));
	print("struct CCache.image %lud\n", offsetof(struct CCache, image));
	print("struct CCache.font %lud\n", offsetof(struct CCache, font));
	print("struct CCache.name %lud\n", offsetof(struct CCache, name));
	print("struct CCache.index %lud\n", offsetof(struct CCache, index));
	print("struct CCache.ref %lud\n", offsetof(struct CCache, ref));
	print("struct CParse %d\n", sizeof(struct CParse));
	print("struct CParse.str %lud\n", offsetof(struct CParse, str));
	print("struct CParse.sender %lud\n", offsetof(struct CParse, sender));
	print("struct CParse.receiver %lud\n", offsetof(struct CParse, receiver));
	print("struct CParse.cmd %lud\n", offsetof(struct CParse, cmd));
	print("struct CParse.pargs %lud\n", offsetof(struct CParse, pargs));
	print("struct CParse.iargs %lud\n", offsetof(struct CParse, iargs));
	print("struct CParse.args %lud\n", offsetof(struct CParse, args));
	print("struct CParse.nargs %lud\n", offsetof(struct CParse, nargs));
	exits(nil);
}
