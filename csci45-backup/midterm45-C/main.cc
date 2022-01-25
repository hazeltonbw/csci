#include <vector>
#include <iostream>
using namespace std;

//Do not modify this file under the punishment of a thousand suns
extern "C" {
	int c_fun_one(int i, int j);
	int c_fun_two(int i, int j);
	int asm_fun_one(int i, int j);
	int asm_fun_two(int i, int j);
}

int main() {
	vector<int> vec1,vec2;
	cout << "Do you want to test function 1 or 2?\n";
	int fun = 0;
	cin >> fun;
	if (!cin || fun < 1 || fun > 2) return 1;
	cout << "Please input a size:\n";
	int N = 0;
	cin >> N;
	if (!cin) return 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (fun == 1) {
				vec1.push_back(c_fun_one(i,j));
				vec2.push_back(asm_fun_one(i,j));
			}
			else {
				vec1.push_back(c_fun_two(i,j));
				vec2.push_back(asm_fun_two(i,j));
			}
			if (vec1.back() != vec2.back()) {
				cout << "Error when i = " << i << " and j = " << j << endl;
				cout << "Correct answer = " << vec1.back() << endl;
				cout << "Your answer = " << vec2.back() << endl;
				return 1;
			}
		}
	}
	cout << "All tests passed!\n";
}
