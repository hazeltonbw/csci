CFLAGS = -std=gnu99 -g
CCFLAGS = -std=c++0x -g

a.out: main.o c_fun.o asm_fun.o
	g++ $(CCFLAGS) main.o c_fun.o asm_fun.o

c_fun.o: c_fun.c
	gcc $(CFLAGS) -c c_fun.c

main.o: main.cc
	g++ $(CCFLAGS) -c main.cc

asm_fun.o: asm_fun.s
	as -o asm_fun.o asm_fun.s

clean:
	rm -f a.out core *.o

