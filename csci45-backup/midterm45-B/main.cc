//You cannot touch anything in this code
#include "/public/read.h"
#include <cstdlib>
using namespace std;

//You can call this function to help you debug your code
extern "C" void print_int (int x) {
	cerr << x << endl;
}

/*
Writes "count" integers to arr starting at arr[index]
Index must be >= 2
What does it write? The fibonacci numbers
Example: c_fibber(arr,2,4) will write into arr the following values
	arr[2] = 2;
	arr[3] = 3;
	arr[4] = 5;
	arr[5] = 8;
Precondition: All elements prior to index have been filled properly
*/
void c_fibber(int *arr, size_t index, size_t count) {
	if (!arr) return;
	if (index < 2) return; //The first two elements are set in main
	for (size_t i = index; i < index+count; i++)
		arr[i] = arr[i-1] + arr[i-2];
}

extern "C" void asm_fibber(int *arr, size_t index, size_t count);

void compare_arrays(int *c_arr, int *asm_arr, int size) {
	for (int i = 0; i < size; i++) {
		if (c_arr[i] != asm_arr[i]) {
			cout << "Your array is different from the c array." << endl;
			exit(EXIT_FAILURE);
		}
	}
}

void print_array(int *arr, int size) {
	for (int i = 0; i < size; i++) cout << arr[i] << " ";
	cout << endl;
}

int main() {
	int size = read("How big an array do you want to make? (Min 10)\n");
	if (size < 10) return 0;
	int *c_arr   = new int[size]{1,1}; //Initialize the first two elements with 1,1
	int *asm_arr = new int[size]{1,1};

	cout << "Trying to seg fault your code..." << endl;
	c_fibber  (NULL,2,size-2);
	asm_fibber(NULL,2,size-2);
	c_fibber  (c_arr,0,2);
	asm_fibber(asm_arr,0,2);
	c_fibber  (c_arr,1,2);
	asm_fibber(asm_arr,1,2);

	//Nothing you did above should change anything, but we'll see
	compare_arrays(c_arr,asm_arr,size);

	//Do the first five as an easy test to see if your code works
	cout << "Fibonacci-ing the first five elements..." << endl;
	c_fibber  (c_arr,2,3);
	asm_fibber(asm_arr,2,3);
	cout << "My   array: ";
	print_array(c_arr,5);
	cout << "Your array: ";
	print_array(asm_arr,5);
	compare_arrays(c_arr,asm_arr,size);

	//Do the next five as well
	cout << "Fibonacci-ing the next five elements..." << endl;
	c_fibber  (c_arr,5,5);
	asm_fibber(asm_arr,5,5);
	cout << "My   array: ";
	print_array(c_arr,10);
	cout << "Your array: ";
	print_array(asm_arr,10);
	compare_arrays(c_arr,asm_arr,size);

	if (size > 10) {
		cout << "Now doing the rest..." << endl;
		c_fibber  (c_arr,10,size-10);
		asm_fibber(asm_arr,10,size-10);
		cout << "My   array: ";
		print_array(c_arr,size);
		cout << "Your array: ";
		print_array(asm_arr,size);
		compare_arrays(c_arr,asm_arr,size);
	}

	delete []c_arr;
	delete []asm_arr;
}
