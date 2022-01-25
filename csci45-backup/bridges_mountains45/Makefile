FLAGS = -g -O1 -std=c++2a -DMAKEFILE -lcurl 
a.out: main.o findPath.o
	g++ $(FLAGS) main.o findPath.o

findPath.o: findPath.s
	as -o findPath.o findPath.s

main.o: main.cc
	g++ $(FLAGS) -c main.cc

clean:
	rm -f a.out *.o core
