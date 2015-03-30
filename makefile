
all:test
test:test.c kfifo.c
	gcc -g -o /tmp/test test.c kfifo.c -lpthread

