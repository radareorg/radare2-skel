all:
	mkdir -p node_modules
	npm i
	r2 -q -c ':. src/r2f-newcmd.js' -c ':test' frida://0

r2f:
	r2frida-compile -o portable.r2.js src/test.r2.ts
