CC=gcc
CFLAGS=-O3 -w -I.
DEPS = bootimg.h fmemopen.h
OBJ = fmemopen.o abootimg.o

all: cpi

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

abootimg: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lbsd

cpi: abootimg

clean:
	rm -f bin/abootimg src/*.o

.PHONY:	clean all
