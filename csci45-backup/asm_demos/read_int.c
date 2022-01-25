//Option 1 (Normal):
//Use this program like this:
//  gcc 7_functions.s read_int.c 

//==========================================================
//Advanced option if you want to learn about shared libraries
//Option 2 (Make it a shared library):
//Or if you want to be super cool, turn this into a .so file:
//  gcc -shared -o libread_int.so read_int.c
//Then compile it like this:
//  gcc 7_functions.s -lread_int -L.
//And make sure that . is in your LD_LIBRARY_PATH (which is where the system searches for .so files)
//Edit your ~/.cshrc and add this line somewhere within it:
//setenv LD_LIBRARY_PATH .
//And now you can run a.out and have it worked with a shared library!
//==========================================================

#include <stdio.h>

//Make reading an int easy from assembly
int read_int() {
	int x = 0;
	scanf("%i",&x);
	return x;
}

void prompt() {
	printf("Please enter three integers. It will compare the first two using both signed and unsigned comparisons, and then tell you if the first one is between the second and third.\n");
}

void print_signed_compare() {
	printf("Doing a signed comparison.\n");
}

void print_unsigned_compare() {
	printf("Doing an unsigned comparison.\n");
}

void less_than(int x, int y) {
	printf("%i is less than %i\n",x,y);
}

void equal_to(int x, int y) {
	printf("%i is equal to %i\n",x,y);
}

void greater_than(int x, int y) {
	printf("%i is greater than %i\n",x,y);
}

void unsigned_less_than(unsigned int x, unsigned int y) {
	printf("%i is less than %i\n",x,y);
}

void unsigned_equal_to(unsigned int x, unsigned int y) {
	printf("%i is equal to %i\n",x,y);
}

void unsigned_greater_than(unsigned int x, unsigned int y) {
	printf("%i is greater than %i\n",x,y);
}

void within(int x, int y, int z) {
	printf("%i is between %i and %i\n",x,y,z);
}

void not_within(int x, int y, int z) {
	printf("%i is not between %i and %i\n",x,y,z);
}
