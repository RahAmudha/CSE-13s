CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror
SRC = $(wildcard *.c)
OBJ = stack.o path.o graph.o tsp.o
EXECBIN = tsp

.PHONY = all clean debug

all: $(EXECBIN)

clean:
	rm -f $(OBJ) $(EXECBIN)

format:
	clang-format -i --style=file *.[ch]

debug: CFLAGS += -g
debug: clean all

$(EXECBIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECBIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $<
