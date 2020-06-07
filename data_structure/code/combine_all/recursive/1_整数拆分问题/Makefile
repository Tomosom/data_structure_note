CC=gcc
CFLAGS= -Wall -g -O0
SRC=${wildcard *.c}
TARGETS=${patsubst %.c, %, $(SRC)}

all:$(TARGETS)

%:%.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(TARGETS) .*.SW?

