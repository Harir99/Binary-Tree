CC=gcc 
CFLAGS=-g -lm -std=c99 -Wall -pedantic

all: tree.o ttest

ttest: ttest.c tree.o tree.h 
	$(CC) $(CFLAGS) ttest.c tree.o -o ttest

ttest.o: ttest.c ttest.o tree.h
	$(CC) $(CFLAGS) -c ttest.c tree.o -o ttest.o

tree: tree.c tree.h 
	$(CC) $(CFLAGS) tree.c -o tree

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c -o tree.o

clean:
	rm -f *.o ttest
