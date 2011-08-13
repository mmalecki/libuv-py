CC = gcc
CFLAGS = -Ideps/uv/include -Wall -Wextra -g -O0 -fPIC

CFLAGS += $(shell python-config --includes)
LDFLAGS += $(shell python-config --ldflags)

.PHONY = all clean

all:	src/uv.o deps/uv/uv.a
	$(CC) -shared -o pyuv.so $^

clean:
	rm -f src/uv.o pyuv.so

distclean:	clean
	$(MAKE) -C deps/uv $@

deps/uv/uv.a:
	$(MAKE) -C deps/uv CFLAGS="-Wall -Wextra -fPIC"
