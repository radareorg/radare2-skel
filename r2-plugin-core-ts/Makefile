all: r2frida-portable
	r2 -i src/coreplug.r2.js /bin/ls

r2frida-portable:
	r2pm -r r2frida-compile -o src/coreplug.r2.js src/coreplug.r2.ts

npmway:
	mkdir -p node_modules
	npm i
	tsc

open:
	open -a "Visual Studio Code" .
