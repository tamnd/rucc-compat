#include <u.h>
#include <libc.h>
#include <draw.h>
#include <mouse.h>
#include <frame.h>

void
main(void)
{
	print("Frbox %.8lux\n", signof(Frbox));
	print("Frame %.8lux\n", signof(Frame));
	print("struct Frbox %.8lux\n", signof(struct Frbox));
	print("struct Frame %.8lux\n", signof(struct Frame));
	print("frcharofpt %.8lux\n", signof frcharofpt);
	print("frptofchar %.8lux\n", signof frptofchar);
	print("frdelete %.8lux\n", signof frdelete);
	print("frinsert %.8lux\n", signof frinsert);
	print("frselect %.8lux\n", signof frselect);
	print("frselectpaint %.8lux\n", signof frselectpaint);
	print("frdrawsel %.8lux\n", signof frdrawsel);
	print("frdrawsel0 %.8lux\n", signof frdrawsel0);
	print("frinit %.8lux\n", signof frinit);
	print("frsetrects %.8lux\n", signof frsetrects);
	print("frclear %.8lux\n", signof frclear);
	print("_frallocstr %.8lux\n", signof _frallocstr);
	print("_frinsure %.8lux\n", signof _frinsure);
	print("_frdraw %.8lux\n", signof _frdraw);
	print("_frgrowbox %.8lux\n", signof _frgrowbox);
	print("_frfreebox %.8lux\n", signof _frfreebox);
	print("_frmergebox %.8lux\n", signof _frmergebox);
	print("_frdelbox %.8lux\n", signof _frdelbox);
	print("_frsplitbox %.8lux\n", signof _frsplitbox);
	print("_frfindbox %.8lux\n", signof _frfindbox);
	print("_frclosebox %.8lux\n", signof _frclosebox);
	print("_frcanfit %.8lux\n", signof _frcanfit);
	print("_frcklinewrap %.8lux\n", signof _frcklinewrap);
	print("_frcklinewrap0 %.8lux\n", signof _frcklinewrap0);
	print("_fradvance %.8lux\n", signof _fradvance);
	print("_frnewwid %.8lux\n", signof _frnewwid);
	print("_frnewwid0 %.8lux\n", signof _frnewwid0);
	print("_frclean %.8lux\n", signof _frclean);
	print("_frdrawtext %.8lux\n", signof _frdrawtext);
	print("_fraddbox %.8lux\n", signof _fraddbox);
	print("_frptofcharptb %.8lux\n", signof _frptofcharptb);
	print("_frptofcharnb %.8lux\n", signof _frptofcharnb);
	print("_frstrlen %.8lux\n", signof _frstrlen);
	print("frtick %.8lux\n", signof frtick);
	print("frinittick %.8lux\n", signof frinittick);
	print("frredraw %.8lux\n", signof frredraw);
	exits(nil);
}
