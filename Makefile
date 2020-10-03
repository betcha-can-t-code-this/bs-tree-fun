CC = gcc
DEBUG = -g -ggdb
CFLAGS = -O2 -std=c99 -fPIC -Wall -Werror

LIB_OBJS = ./src/tree.o
SHARED_LIB = ./libtree.so

$(SHARED_LIB): $(LIB_OBJS)
	$(CC) $(DEBUG) -shared -Wl,--export-dynamic $(LIB_OBJS) -o $(SHARED_LIB)

tree_test:
	$(CC) $(DEBUG) -o tree_test tree_test.c $(SHARED_LIB)

clean:
	rm -f ./src/*.o
	rm -f ./libtree.so
	rm -f ./tree_test

.PHONY: clean tree_test
