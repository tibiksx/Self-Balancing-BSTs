CC=gcc
CFLAGS=-I.
DEPS=main.c avl.h redBlack.h splay.h treap.h scapegoat.h

OBJ := main.o avl.o redBlack.o splay.o treap.o scapegoat.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

exec: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o exec
