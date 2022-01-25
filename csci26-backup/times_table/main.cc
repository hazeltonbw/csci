#include <iostream>
#include <vector>
using namespace std;

void die() {cout << "BAD INPUT!\n"; exit(EXIT_FAILURE);}

int main() {
	cout << "Choose:" << endl <<
			"1. Addition Table" << endl <<
			"2. Times Table" << endl;

	int choice;
	cin >> choice;
	const int ADDITION = 1;
	const int MULTIPLICATION = 2;
	if (!cin or choice < ADDITION or choice > MULTIPLICATION) die();

	int min = 0, max = 0;
	cout << "Please enter the smallest number on the table:\n";
	cin >> min; if (!cin) die();
	cout << "Please enter the largest number on the table:\n";
	cin >> max; if (!cin) die();

	const int MIN_SIZE = 0, MAX_SIZE = 20;
	if ( max - min >= MAX_SIZE or max - min < MIN_SIZE) die();
	if (choice == ADDITION) {
		cout << "+";
		for (int i = min; i < max + 1; i++)
			cout << "\t" << i;
		cout << endl;
		for (int i = min; i < max + 1; i++) {
			cout << i;
			for (int j = min; j < max + 1; j++) {
				cout << "\t" << i + j;
			}
			cout << endl;
		}
	}
	if (choice == MULTIPLICATION){
		cout << "X";
		for (int i = min; i < max + 1; i++)
			cout << "\t" << i;
		cout << endl;

		for (int i = min; i < max + 1; i++) {
			cout << i << "\t";
			for (int j = min; j < max + 1; j++) {
				cout << i * j << "\t";
			}
			cout << endl;
		}
	}
}
