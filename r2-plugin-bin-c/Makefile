LIBEXT=$(shell r2 -HR2_LIBEXT)
CFLAGS+=$(shell pkg-config --cflags r_bin)
LDFLAGS+=$(shell pkg-config --libs r_bin)
R2_USER_PLUGINS=$(shell r2 -HR2_USER_PLUGINS)

BIN_HELLO=src/bin_hello.$(LIBEXT)
OBJS=src/bin_hello.o

all: $(BIN_HELLO)

$(BIN_HELLO): $(OBJS)
	$(CC) $(LDFLAGS) -shared -fPIC -o $(BIN_HELLO) $(OBJS)

clean:
	rm -f $(OBJS) $(BIN_HELLO)

user-install install:
	mkdir -p $(R2_USER_PLUGINS)
	cp -f $(BIN_HELLO) $(R2_USER_PLUGINS)

user-uninstall uninstall:
	rm -f $(R2_USER_PLUGINS)/$(BIN_HELLO)
