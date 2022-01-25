#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

const size_t ROWS = 5, COLS = 14, PLANES = 3;

extern "C" void asm_arr(int *arr,int *end);

inline size_t index(size_t plane, size_t row, size_t col) {
	return plane*ROWS*COLS + row*COLS + col;
}

int main() {
	const size_t SIZE = PLANES*ROWS*COLS;
	cout << sizeof(size_t) << endl;

	//int arr[PLANES][ROWS][COLS];
	int arr[SIZE];
	for (size_t i = 0; i < SIZE; i++) {
		arr[i] = 10*i;
	}
	cout << "BEFORE:\n";
	for (size_t i = 0; i < PLANES; i++) {
		for (size_t j = 0; j < ROWS; j++) {
			for (size_t k = 0; k < COLS; k++) {
				//cout << setw(4) << arr[i*ROWS*COLS + j*COLS + k] << " ";
				cout << setw(4) << arr[index(i,j,k)] << " ";
			}
			cout << endl;
		}
		cout << "==========================" << endl;
	}
	asm_arr(arr,arr+PLANES*ROWS*COLS);
	cout << "AFTER:\n";
	for (size_t i = 0; i < PLANES; i++) {
		for (size_t j = 0; j < ROWS; j++) {
			for (size_t k = 0; k < COLS; k++) {
				//cout << setw(4) << arr[i*ROWS*COLS + j*COLS + k] << " ";
				cout << setw(4) << arr[index(i,j,k)] << " ";
			}
			cout << endl;
		}
		cout << "==========================" << endl;
	}
}
