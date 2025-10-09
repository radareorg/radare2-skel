project('core-hello-go', 'c', 'go', license : 'MIT', meson_version : '>=1.00', version : '0.1.0')

r2_plugdir = run_command('r2', '-H', 'R2_USER_PLUGINS', check: true).stdout().strip()

# Note: Building Go plugins with cgo requires special handling
# Use the provided Makefile for building

# For now, assume the Makefile is used