FLAGS = -O2 -falign-functions=1 -falign-jumps=1 -falign-loops=1 -falign-labels=1 

a.out: main.o asm_spongebob.o
	g++ $(FLAGS) main.o asm_spongebob.o

asm_spongebob.o: asm_spongebob.s
	as -o asm_spongebob.o asm_spongebob.s

main.o: main.cc
	g++ $(FLAGS) -c main.cc

clean:
	rm -f a.out core *.o
