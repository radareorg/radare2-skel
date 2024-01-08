R2PM_BINDIR=$(shell r2pm -H R2PM_BINDIR)
R2_BINDIR=$(shell r2 -H R2_BINDIR)
R2_PREFIX=$(shell r2 -H R2_PREFIX)
SYS_SKEL_DIR=$(R2_PREFIX)/share/radare2/r2skel
PWD=$(shell pwd)

all:
	@echo "Run 'make user-install or 'make install'"

user-install:
	ln -fs ${PWD}/r2skel ${R2PM_BINDIR}/r2skel

user-uninstall:
	rm -f ${R2PM_BINDIR}/r2skel

install:
	$(MAKE) uninstall
	mkdir -p $(SYS_SKEL_DIR)
	cp -rf * $(SYS_SKEL_DIR)
	ln -fs $(SYS_SKEL_DIR)/r2skel $(R2_BINDIR)/r2skel

uninstall:
	rm -rf $(SYS_SKEL_DIR)
	rm -f $(R2_BINDIR)/r2skel
