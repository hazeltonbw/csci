a.out: main.o asm_if.o
	gcc -O3 main.o asm_if.o

asm_if.o: asm_if.s
	as -o asm_if.o asm_if.s

main.o: main.c
	gcc -O3 -c -std=c99 main.c

clean:
	rm -f a.out core *.o
