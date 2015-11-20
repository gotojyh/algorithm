
all:test testmacro
test:test.c kfifo.c
	gcc -g -o /tmp/test test.c kfifo.c -lpthread
%:%.c
	gcc -g -o /tmp/$@ $<

