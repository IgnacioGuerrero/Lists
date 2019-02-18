# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=gcc
CFLAGS = -Wall -g
#DEPS = some.h
OBJ = LinkedList.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

LinkedList: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm LinkedList
#LinkedList: LinkedList.c
#	gcc -Wall -o LinkedList LinkedList.c