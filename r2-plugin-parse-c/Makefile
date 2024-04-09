LIBEXT=$(shell r2 -HR2_LIBEXT)
CFLAGS+=$(shell pkg-config --cflags r_arch)
LDFLAGS+=$(shell pkg-config --libs r_arch)
R2_USER_PLUGINS=$(shell r2 -HR2_USER_PLUGINS)

PARSE_HELLO=src/parse_hello.$(LIBEXT)
OBJS=src/parse_hello.o

all: $(PARSE_HELLO)

$(PARSE_HELLO): $(OBJS)
	$(CC) $(LDFLAGS) -shared -fPIC -o $(PARSE_HELLO) $(OBJS)

clean:
	rm -f $(OBJS) $(PARSE_HELLO)

user-install install:
	mkdir -p $(R2_USER_PLUGINS)
	cp -f $(PARSE_HELLO) $(R2_USER_PLUGINS)

user-uninstall uninstall:
	rm -f $(R2_USER_PLUGINS)/$(PARSE_HELLO)
