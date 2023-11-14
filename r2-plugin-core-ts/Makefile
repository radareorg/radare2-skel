all:
	mkdir -p node_modules
	npm i
	tsc
	r2 -q -i src/coreplug.r2.ts /bin/ls

r2frida-portable:
	r2frida-compile -o portable.r2.js src/test.r2.ts

open:
	open -a "Visual Studio Code" .
