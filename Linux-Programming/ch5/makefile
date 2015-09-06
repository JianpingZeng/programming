copy.o: copy.c copy.h
	clang -c copy.c
main.o: main.c
	clang -c main.c
copy: copy.o main.o
	clang -o copy copy.o main.o
clean:
	rm -r *.o

