#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	string str;
	cout << argc - 1 << " arguments after executable " << endl;
	cout << "Arguments: ";
	for (int i = 0; i < argc; i++) {
		cout << argv[i] << " ";
	}
	cout << endl;
	getline(cin,str);
	for (size_t i = 0; i < str.size(); i++) {
		cout << str[i] << endl;
	}

	for (char c : str) {
		cout << c;
	}
	cout << endl;
}
