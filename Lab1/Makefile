CC = gcc
CFLAGS = -Wall -g
LD = gcc
LDFLAGS = -g

OBJS = lab1.o

all: lab1.out

lab1.out: $(OBJS)
	$(LD) $(LDFLAGS) -o myls $^

.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -f *.o myls


