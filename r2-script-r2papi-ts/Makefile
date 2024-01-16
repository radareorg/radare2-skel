all:
	mkdir -p node_modules
	npm i
	node_modules/.bin/tsc || tsc
	r2 -q -i src/test.r2.ts /bin/ls
	r2frida-compile -o portable.r2.js src/test.r2.ts
