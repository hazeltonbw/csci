CC=g++-10
#CCFLAGS = -O3 -std=c++2a -fsanitize=address -fsanitize=undefined
CCFLAGS = -std=c++17 -g
LIBS = -lcurl

a.out: main.cc
	$(CC) $(CCFLAGS) -DUSING_MAKEFILE main.cc $(LIBS)

clean:
	rm -rf *.o a.out core
