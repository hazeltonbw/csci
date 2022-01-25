#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

//We provide a simple number printer for your assembly code
void print_number(int x) {
	printf("%i\n",x);
}

//This is the code you will write - it can be found in iota.s
extern void iota(int *arr, int size, int starting_value); 

//This is the reference implementation in C that you must write in assembly
//(Minus the warning, of course, which is there to make sure you're compiling it right.)
void reference_iota(int *arr, int size, int starting_value) {
	printf("WARNING: You're still running the reference implementation.\n");
	for (int i = 0; i < size; i++) 
		arr[i] = starting_value++;
}

//You shouldn't need to modify the code below, unless you want to try reference_iota to see how it works
int main() {
	int size,starting_value,*guard,*arr;
	printf("Welcome to the Iota Simulator 2000.\n");
	printf("Please enter how big an array you want to iota: ");
	scanf("%i",&size);
	printf("Please enter the value you want to start with: ");
	scanf("%i",&starting_value);
	if (size < 1 || size > MAX_SIZE) {
		printf("Invalid size\n");
		exit(EXIT_FAILURE);
	}
	//Create a bigger array to test students for memory overruns
	guard = (int *)malloc(sizeof(int) * size+2);
	guard[0] = guard[size+1] = 42; //Set up some guard values to check for overruns
	//Build arr inside of guard
	arr = &guard[1];
	printf("Calling iota...\n");
	iota(arr,size,starting_value); //Call the student's code
	//reference_iota(arr,size,starting_value); //Call the reference code
	printf("Here is your array: ");
	for (int i = 0; i < size; i++) 
		printf("[%i]",arr[i]);
	printf("\nThe guard values should be 42 and 42. They are: %i and %i\n",guard[0],guard[size+1]);
}
