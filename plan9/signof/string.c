#include <u.h>
#include <libc.h>
#include <String.h>

void
main(void)
{
	print("String %.8lux\n", signof(String));
	print("struct String %.8lux\n", signof(struct String));
	print("s_append %.8lux\n", signof s_append);
	print("s_array %.8lux\n", signof s_array);
	print("s_copy %.8lux\n", signof s_copy);
	print("s_free %.8lux\n", signof s_free);
	print("s_incref %.8lux\n", signof s_incref);
	print("s_memappend %.8lux\n", signof s_memappend);
	print("s_nappend %.8lux\n", signof s_nappend);
	print("s_new %.8lux\n", signof s_new);
	print("s_newalloc %.8lux\n", signof s_newalloc);
	print("s_parse %.8lux\n", signof s_parse);
	print("s_reset %.8lux\n", signof s_reset);
	print("s_restart %.8lux\n", signof s_restart);
	print("s_terminate %.8lux\n", signof s_terminate);
	print("s_tolower %.8lux\n", signof s_tolower);
	print("s_putc %.8lux\n", signof s_putc);
	print("s_unique %.8lux\n", signof s_unique);
	print("s_grow %.8lux\n", signof s_grow);
	exits(nil);
}
