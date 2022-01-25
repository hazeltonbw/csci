/* DO NOT MODIFY THIS FILE OR THE WRATH OF A THOUSAND SUNS WILL BE BROUGHT UPON YOUR GRADE */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int asm_if(int a, int b, int c, int d);

//This is the function y'all will write in asm
int c_if(int a, int b, int c, int d) {
	return ((a | b) && (c | d)) || ((a | ~d) & (~b & d));
}

int main() {
	const int SIZE = 16;
	int answers[SIZE]; //Holds the results in memory
	for (int i = 0; i < SIZE; i++) {
		int a = i & 1; //See kids, bitwise operations are fun!
		int b = i & 2;
		int c = i & 4;
		int d = i & 8;
		answers[i] = c_if(a,b,c,d);
		fprintf(stderr, "Answer %i: %i\n",i,answers[i]);
	}
	const int LOOPS = 10000000;
	printf("Calling your assembly code %i times...\n",LOOPS);
	clock_t start_time = clock();
	for (int i = 0; i < LOOPS; i++) {
		int a = i & 1; //See kids, bitwise operations are fun!
		int b = i & 2;
		int c = i & 4;
		int d = i & 8;
		int index = i & 0x0000000F; //Fast modulus 16
		int answer = asm_if(a,b,c,d);
		if (answer != answers[index]) {
			printf("Error: your function was wrong for test case %i: %i %i %i %i\n",index,a,b,c,d);

			exit(EXIT_FAILURE);
		}
	}
	fprintf(stderr,"Milliseconds elapsed: %i\n",(clock() - start_time)/1000);
}
