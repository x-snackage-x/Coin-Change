CC=cc
CFLAGS=-I.
DEPS = coin-change.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cli: coin-change.o coin-change-cli.o
	$(CC) -o coin-change-cli.e coin-change.o coin-change-cli.o

test: coin-change.o coin-change-c.o
	$(CC) -o coin-change-c.e coin-change.o coin-change-c.o
