LIBEXT=$(shell r2 -HR2_LIBEXT)
CFLAGS+=$(shell pkg-config --cflags r_fs)
LDFLAGS+=$(shell pkg-config --libs r_fs)
R2_USER_PLUGINS=$(shell r2 -HR2_USER_PLUGINS)

FS_HELLO=src/fs_hello.$(LIBEXT)
OBJS=src/fs_hello.o

all: $(FS_HELLO)

$(FS_HELLO): $(OBJS)
	$(CC) $(LDFLAGS) -shared -fPIC -o $(FS_HELLO) $(OBJS)

clean:
	rm -f $(OBJS) $(FS_HELLO)

user-install install:
	mkdir -p $(R2_USER_PLUGINS)
	cp -f $(FS_HELLO) $(R2_USER_PLUGINS)

user-uninstall uninstall:
	rm -f $(R2_USER_PLUGINS)/$(FS_HELLO)
