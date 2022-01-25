#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
using namespace std;

int fib(int n) {
	if (n < 2) return n;
	return fib(n-1) + fib(n-2);
}

int main() {
	int number = 0;
	cin >> number;
	cout << "The fibonnaci sequence of " << number << " is: " << fib(number) << endl;
}
