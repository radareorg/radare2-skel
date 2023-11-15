LIBEXT=$(shell r2 -HR2_LIBEXT)
CFLAGS+=$(shell pkg-config --cflags r_io)
LDFLAGS+=$(shell pkg-config --libs r_io)
R2_USER_PLUGINS=$(shell r2 -HR2_USER_PLUGINS)

IO_HELLO=src/io_hello.$(LIBEXT)
OBJS=src/io_hello.o

all: $(IO_HELLO)

$(IO_HELLO): $(OBJS)
	$(CC) $(LDFLAGS) -shared -fPIC -o $(IO_HELLO) $(OBJS)

clean:
	rm -f $(OBJS) $(IO_HELLO)

user-install install:
	mkdir -p $(R2_USER_PLUGINS)
	cp -f $(IO_HELLO) $(R2_USER_PLUGINS)

user-uninstall uninstall:
	rm -f $(R2_USER_PLUGINS)/$(IO_HELLO)
