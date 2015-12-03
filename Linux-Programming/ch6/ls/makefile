#define compiler
cc = gcc
cflags = -g
#define objective file
obj = node.o display.o ls.o

ls: $(obj)
	cc -o $(cflags) $(obj) -std=gnu99
node.o: node.c node.h	
	cc -c  $(cflags) node.c -std=gnu99
display.o: display.c display.h
	cc -c $(cflags) display.c -std=gnu99

.PHONY:clean
clean:
	rm -r *.o *~

