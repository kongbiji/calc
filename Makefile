CC=gcc
CFLAGS=-g -Wall
OBJS=calc.o
TARGET=calc

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

calc.o : function.h calc.c

clean:
	rm -f *.o