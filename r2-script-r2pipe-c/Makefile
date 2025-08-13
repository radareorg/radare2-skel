CC = cc
PKG = r_socket
CFLAGS = $(shell pkg-config --cflags $(PKG) 2>/dev/null)
LDLIBS = $(shell pkg-config --libs $(PKG) 2>/dev/null)

TARGET = hello

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $@ main.c $(LDLIBS)

clean:
	rm -f $(TARGET)
