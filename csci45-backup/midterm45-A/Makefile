a.out: main.o io.o
	gcc main.o io.o

main.o: main.s
	gcc -c -g main.s

io.o: io.c
	gcc -c -g io.c

clean:
	rm -f a.out core *.o
