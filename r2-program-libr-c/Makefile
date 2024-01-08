R2_FLAGS=$(shell pkg-config --cflags --libs r_core)

all:
	$(CC) test.c $(R2_FLAGS) -o test
	./test
