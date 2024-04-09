project('parse-hello', 'c', license : 'MIT', meson_versparsen : '>=1.00', versparsen : '0.1.0')

r2_plugdir = run_command('r2', '-H', 'R2_USER_PLUGINS', check: true).stdout().strip()

sources = [ 'src/parse_hello.c' ]
lib = library('parsehello', sources,
	dependencies : [
		dependency('r_arch')
	],
	install_dir: r2_plugdir,
	install: true
)
