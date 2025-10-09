LIBEXT=$(shell r2 -HR2_LIBEXT)
CFLAGS+=$(shell pkg-config --cflags r_core) -fPIC
LDFLAGS+=$(shell pkg-config --libs r_core) -fPIC
R2_USER_PLUGINS=$(shell r2 -HR2_USER_PLUGINS)

LIBCORE_HELLO=core_hello.$(LIBEXT)
CORE_HELLO=src/$(LIBCORE_HELLO)

all: $(CORE_HELLO)

$(CORE_HELLO):
	GOCACHE=$(GOCACHE) GO111MODULE=off CGO_CFLAGS="$(CFLAGS)" CGO_LDFLAGS="$(LDFLAGS)" go build -buildmode=c-shared -o $(CORE_HELLO) ./src

clean:
	rm -f $(CORE_HELLO)
	rm -rf $(GOCACHE)
	rm -f src/core_hello.o

test:
	r2 -i $(CORE_HELLO) -qc hello --

user-install install:
	mkdir -p $(R2_USER_PLUGINS)
	cp -f $(CORE_HELLO) $(R2_USER_PLUGINS)

user-uninstall uninstall:
	rm -f $(R2_USER_PLUGINS)/$(LIBCORE_HELLO)

GOCACHE?=$(CURDIR)/.gocache
