LIBEXT=dylib
R2_USER_PLUGINS=$(shell r2 -HR2_USER_PLUGINS 2>/dev/null | tail -1 || echo "$$HOME/.local/share/radare2/plugins")

CORE_HELLO=core_hello.$(LIBEXT)

all: $(CORE_HELLO)

$(CORE_HELLO):
	cc -c Sources/CRadare2/CoreHelloShim.c -I/usr/local/include/libr -o CoreHelloShim.o
	swiftc -emit-library -o $(CORE_HELLO) Sources/CoreHello/CoreHello.swift CoreHelloShim.o -L/usr/local/lib -lr_core -lr_config -lr_debug -lr_bin -lr_lang -lr_anal -lr_bp -lr_egg -lr_asm -lr_flag -lr_search -lr_syscall -lr_fs -lr_io -lr_socket -lr_cons -lr_magic -lr_muta -lr_arch -lr_esil -lr_reg -lr_util
	rm -f CoreHelloShim.o

clean:
	rm -rf .build $(CORE_HELLO)

user-install install:
	mkdir -p $(R2_USER_PLUGINS)
	cp -f $(CORE_HELLO) $(R2_USER_PLUGINS)

user-uninstall uninstall:
	rm -f $(R2_USER_PLUGINS)/$(CORE_HELLO)