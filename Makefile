R2PM_BINDIR=$(shell r2pm -H R2PM_BINDIR)
PWD=$(shell pwd)

all:
	ln -fs ${PWD}/r2skel ${R2PM_BINDIR}/r2skel
