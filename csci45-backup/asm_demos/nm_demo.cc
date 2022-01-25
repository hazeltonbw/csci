//No #includes are here to make this code simple

//Compile this code a couple different ways and look at how the symbol table changes:
//  Option 1) \g++ nm_demo.cc (standard compilation)
//  Option 2) g++ test.cc -static -static-libstdc++ (staticly linked compilation)
//  Option 3) g++ test.cc -g -fsanitize=address (enable ASAN and debugging)
//  Option 4) g++ -nostdlib -fno-exceptions -fno-rtti -Os nm_demo.cc (no standard library, RTTI, execeptions, optimized to minimized executable size, this will also not work)
//Then look at the symbol table like this: nm a.out
//Also do a ls -l on each a.out you make "ls -l a.out" and see how the executable size changes
int some_global; //"B" - Located in the BSS - zero-initialized global segment
int some_other_global = 2; //"D" - Located in the initialized data segment

//T means the code is in the text section (which means code)
//Here is what nm has to say about this function: "00010454 T _Z4add4iiii"
//The first number is the memory offset in hex from the start of the executable
//The weird name of this function is the result of C++ name mangling
//I think _Z is how every function starts, 4 is the letters in the function name, add4 is the name, iiii is the types of the parameters
int add4(int a, int b, int c, int d) {
	return a+b+c+d;
}

//Uncomment this to get an assembler error
//extern "C" void _Z4add4iiii() {
//}

//This one is similar, but takes 6 ints by value instead of 4:
//000104b4 T _Z7add_sixiiiiii
int add_six(int a, int b, int c, int d, int e, int f) {
	return a+b+c+d+e+f;
}

//Similar but takes a referebce to an integer:
//000104f4 T _Z14make_fourtytwoRi
int make_fourtytwo(int &a) {
	a = 42;
	return a;
}

//Boring function - v (void) is the parameter type
//00010528 T _Z3foov
void foo() {}
//This would also work: void foo(void) {}

//Theres an undefined reference to abort:
//         U abort@@GLIBC_2.4
//Note that it carries what version of the GNU LibC that it needs to run. If you don't have that installed, your program will fail to load! This happens to me sometimes when installing the newest compilers. It'll compile executables with dependencies that aren't installed on my machine yet. So I have to statically compile my programs instead.

//main doesn't get name mangled!
//00010540 T main
int main() {
	int x = 0;
	make_fourtytwo(x); //Sets x to 42;
	x += add4(42,54,64,74);
	x += add_six(42,54,64,74,-10,-20);
	return x;
}
