#include <u.h>
#include <libc.h>
#include <draw.h>
#include <mouse.h>
#include <control.h>

void
main(void)
{
	print("Control %.8lux\n", signof(Control));
	print("Controlset %.8lux\n", signof(Controlset));
	print("CParse %.8lux\n", signof(CParse));
	print("CCache %.8lux\n", signof(CCache));
	print("CImage %.8lux\n", signof(CImage));
	print("CFont %.8lux\n", signof(CFont));
	print("struct Controlset %.8lux\n", signof(struct Controlset));
	print("struct Control %.8lux\n", signof(struct Control));
	print("struct CCache %.8lux\n", signof(struct CCache));
	print("struct CParse %.8lux\n", signof(struct CParse));
	print("ctltypenames %.8lux\n", signof ctltypenames);
	print("_ctladdgroup %.8lux\n", signof _ctladdgroup);
	print("_ctlargcount %.8lux\n", signof _ctlargcount);
	print("_createctl %.8lux\n", signof _createctl);
	print("_ctlrunestr %.8lux\n", signof _ctlrunestr);
	print("_ctlstrrune %.8lux\n", signof _ctlstrrune);
	print("_ctlputsnarf %.8lux\n", signof _ctlputsnarf);
	print("_ctlgetsnarf %.8lux\n", signof _ctlgetsnarf);
	print("_ctlalignment %.8lux\n", signof _ctlalignment);
	print("_ctlalignpoint %.8lux\n", signof _ctlalignpoint);
	print("_ctlfocus %.8lux\n", signof _ctlfocus);
	print("_activategroup %.8lux\n", signof _activategroup);
	print("_deactivategroup %.8lux\n", signof _deactivategroup);
	print("_ctllookup %.8lux\n", signof _ctllookup);
	print("_ctlprint %.8lux\n", signof _ctlprint);
	print("_getctlimage %.8lux\n", signof _getctlimage);
	print("_setctlimage %.8lux\n", signof _setctlimage);
	print("_putctlimage %.8lux\n", signof _putctlimage);
	print("_getctlfont %.8lux\n", signof _getctlfont);
	print("_putctlfont %.8lux\n", signof _putctlfont);
	print("_setctlfont %.8lux\n", signof _setctlfont);
	print("namectlimage %.8lux\n", signof namectlimage);
	print("freectlimage %.8lux\n", signof freectlimage);
	print("namectlfont %.8lux\n", signof namectlfont);
	print("freectlfont %.8lux\n", signof freectlfont);
	print("ctlprint %.8lux\n", signof ctlprint);
	print("initcontrols %.8lux\n", signof initcontrols);
	print("newcontrolset %.8lux\n", signof newcontrolset);
	print("closecontrolset %.8lux\n", signof closecontrolset);
	print("closecontrol %.8lux\n", signof closecontrol);
	print("ctlerror %.8lux\n", signof ctlerror);
	print("controlcalled %.8lux\n", signof controlcalled);
	print("ctlmalloc %.8lux\n", signof ctlmalloc);
	print("ctlrealloc %.8lux\n", signof ctlrealloc);
	print("ctlstrdup %.8lux\n", signof ctlstrdup);
	print("controlwire %.8lux\n", signof controlwire);
	print("activate %.8lux\n", signof activate);
	print("deactivate %.8lux\n", signof deactivate);
	print("createbox %.8lux\n", signof createbox);
	print("createbutton %.8lux\n", signof createbutton);
	print("createcolumn %.8lux\n", signof createcolumn);
	print("createboxbox %.8lux\n", signof createboxbox);
	print("createentry %.8lux\n", signof createentry);
	print("createkeyboard %.8lux\n", signof createkeyboard);
	print("createlabel %.8lux\n", signof createlabel);
	print("createmenu %.8lux\n", signof createmenu);
	print("createradiobutton %.8lux\n", signof createradiobutton);
	print("createrow %.8lux\n", signof createrow);
	print("createscribble %.8lux\n", signof createscribble);
	print("createslider %.8lux\n", signof createslider);
	print("createstack %.8lux\n", signof createstack);
	print("createtab %.8lux\n", signof createtab);
	print("createtext %.8lux\n", signof createtext);
	print("createtextbutton %.8lux\n", signof createtextbutton);
	print("createtextbutton3 %.8lux\n", signof createtextbutton3);
	print("resizecontrolset %.8lux\n", signof resizecontrolset);
	print("_ctlsnarffd %.8lux\n", signof _ctlsnarffd);
	print("alignnames %.8lux\n", signof alignnames);
	print("ctldeletequits %.8lux\n", signof ctldeletequits);
	exits(nil);
}
