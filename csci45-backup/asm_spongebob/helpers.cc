#include <iostream>
using namespace std;
extern "C" {
	void print_char(char c) {
		cout << c;	
	}
}
