//Compile with g++ 2d_arrays.cc 20_2d_arrays.s
#include "/public/read.h"
using namespace std;

extern "C" void asm_print_array(int *arr, size_t ROWS, size_t COLS);
extern "C" void print_int(int x) { cout << x; }
extern "C" void print_space() { cout << " "; }
extern "C" void print_newline() { cout << endl; }

void print_array(int *arr, size_t ROWS, size_t COLS) {
	for (size_t i = 0; i < ROWS; i++) {
		for (size_t j = 0; j < COLS; j++) 
			cout << arr[i*COLS+j] << " ";
		cout << endl;
	}
}



int main() {
	const size_t ROWS = read("Please enter how many rows you want:\n");
	const size_t COLS = read("Please enter how many cols you want:\n");
	int *arr = new int[ROWS*COLS];
	for (size_t i = 0; i < ROWS; i++) 
		for (size_t j = 0; j < COLS; j++) 
			arr[i*COLS+j] = 100*i+j;
	cout << "Printing the array in C++:\n";
	print_array(arr,ROWS,COLS);
	cout << "Printing the array in asm:\n";
	asm_print_array(arr,ROWS,COLS);
}
