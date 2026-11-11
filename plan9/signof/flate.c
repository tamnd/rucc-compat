#include <u.h>
#include <libc.h>
#include <flate.h>

void
main(void)
{
	print("deflateinit %.8lux\n", signof deflateinit);
	print("deflate %.8lux\n", signof deflate);
	print("inflateinit %.8lux\n", signof inflateinit);
	print("inflate %.8lux\n", signof inflate);
	print("inflateblock %.8lux\n", signof inflateblock);
	print("deflateblock %.8lux\n", signof deflateblock);
	print("deflatezlib %.8lux\n", signof deflatezlib);
	print("inflatezlib %.8lux\n", signof inflatezlib);
	print("inflatezlibblock %.8lux\n", signof inflatezlibblock);
	print("deflatezlibblock %.8lux\n", signof deflatezlibblock);
	print("flateerr %.8lux\n", signof flateerr);
	print("mkcrctab %.8lux\n", signof mkcrctab);
	print("blockcrc %.8lux\n", signof blockcrc);
	print("adler32 %.8lux\n", signof adler32);
	exits(nil);
}
