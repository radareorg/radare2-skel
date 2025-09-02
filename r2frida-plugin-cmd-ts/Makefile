all:
	mkdir -p node_modules
	r2pm -r r2frida-compile -i
	r2pm -r r2frida-compile -o /dev/null src/r2f-newcmd.ts
	r2 -q -c ':. src/r2f-newcmd.ts' -c ':test' frida://0

clean:
	rm -rf node_modules
