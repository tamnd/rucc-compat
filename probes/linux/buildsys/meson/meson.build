# The questions that a typical meson project asks about the compiler. The answers go to summary.txt.
project('fixture', 'c')

cc = meson.get_compiler('c')
lines = [
  'id=' + cc.get_id(),
  'version=' + cc.version(),
  'linker=' + cc.get_linker_id(),
  'argument_syntax=' + cc.get_argument_syntax(),
  'underscore=' + cc.symbols_have_underscore_prefix().to_string(),
  'stdc_version=' + cc.get_define('__STDC_VERSION__'),
  'sizeof_long=' + cc.sizeof('long').to_string(),
  'sizeof_long_double=' + cc.sizeof('long double').to_string(),
  'alignment_long_double=' + cc.alignment('long double').to_string(),
  'sizeof_int128=' + cc.sizeof('__int128').to_string(),
]
foreach h : ['sys/epoll.h', 'threads.h', 'stdatomic.h', 'sys/random.h', 'valgrind/valgrind.h']
  lines += 'header ' + h + '=' + cc.has_header(h).to_string()
endforeach
foreach f : ['memfd_create', 'getrandom', 'strlcpy', 'reallocarray', 'qsort_r', '__builtin_expect', '__builtin_bswap64', '__builtin_unreachable']
  lines += 'function ' + f + '=' + cc.has_function(f, args: '-D_GNU_SOURCE').to_string()
endforeach
foreach a : ['-Wall', '-Wextra', '-Wformat=2', '-Wno-unused-parameter', '-Wimplicit-fallthrough', '-Wthis-is-not-a-warning', '-fstack-protector-strong', '-fstack-clash-protection', '-fcf-protection', '-fvisibility=hidden', '-ffunction-sections', '-fno-plt', '-fno-semantic-interposition', '-fno-strict-aliasing', '-flto', '-fsanitize=address', '-fopenmp', '-march=native', '-std=gnu17', '-std=c23']
  lines += 'argument ' + a + '=' + cc.has_argument(a).to_string()
endforeach
foreach a : ['-Wl,--as-needed', '-Wl,-z,relro', '-Wl,-z,now', '-Wl,--gc-sections', '-Wl,--no-undefined', '-Wl,-O1', '-Wl,--build-id']
  lines += 'link_argument ' + a + '=' + cc.has_link_argument(a).to_string()
endforeach
foreach a : ['visibility:hidden', 'constructor', 'destructor', 'format', 'alias', 'ifunc', 'weak', 'cold', 'noreturn', 'used', 'unused', 'aligned', 'packed', 'fallthrough', 'nonnull', 'returns_nonnull', 'warn_unused_result', 'always_inline', 'noinline', 'malloc', 'alloc_size', 'sentinel', 'deprecated', 'optimize', 'section', 'error', 'warning', 'retain']
  lines += 'attribute ' + a + '=' + cc.has_function_attribute(a).to_string()
endforeach
lines += 'libm=' + cc.find_library('m', required: false).found().to_string()
lines += 'libdl=' + cc.find_library('dl', required: false).found().to_string()
threads = dependency('threads')
lines += 'threads=' + threads.found().to_string()
lines += 'atomic=' + cc.links('#include <stdatomic.h>\nint main(void) { _Atomic long long x = 0; return (int)atomic_fetch_add(&x, 1); }', name: 'atomics').to_string()
lines += 'pic=' + ' '.join(cc.get_supported_arguments(['-fPIC']))

configure_file(output: 'summary.txt', configuration: {'LINES': '\n'.join(lines)}, input: 'summary.in')

fix = shared_library('fix', 'fix.c', dependencies: cc.find_library('m'))
executable('main', 'main.c', link_with: fix, dependencies: threads)
