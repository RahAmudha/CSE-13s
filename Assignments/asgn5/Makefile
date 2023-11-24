CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror
LFLAGS = -lm
SRC = $(wildcard *.c)
OBJ = io.o bmp.o colorb.o
EXECBIN = colorb
OBJ2 = io.o iotest.o

.PHONY = all clean debug

all: colorb iotest

clean:
	rm -f colorb iotest $(OBJ) $(OBJ2)

format:
	clang-format -i --style=file *.[ch]

debug: CFLAGS += -g
debug: clean all

colorb: $(OBJ)
	$(CC) $(LFLAGS) -o colorb $(OBJ)

iotest: $(OBJ2)
	$(CC) $(LFLAGS) -o iotest $(OBJ2)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

scan-build: clean
	scan-build --use-cc=$(CC) make
