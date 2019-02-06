# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=gcc
CFLAGS = -Wall -g
#DEPS = some.h
OBJ = LinkedList0.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

LinkedList0: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm LinkedList0
#LinkedList0: LinkedList0.c
#	gcc -o LinkedList0 LinkedList0.c