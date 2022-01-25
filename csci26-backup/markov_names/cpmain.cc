#include <iostream>
#include <assert.h>
#include <unordered_map>
#include <vector>
#include <fstream>
using namespace std;

const unsigned int VEC_SIZE = 27;

struct Word {
	string word;
	// TODO
};
void die() {cout << "BAD INPUT!\n"; exit(EXIT_FAILURE);}
void uppercasify(string &s) { for (char &c: s) c = toupper(c); }
void printVector(vector<vector<int>> &letter_occurence_map) {
	// HEADER [A-Z] $
	for (int i = 65; i <= 91; i++) {
		if (i == 65) cout << "  ";
		if (i == 91) cout << "$";
		else cout << char(i) << " ";
	}
	cout << endl;

	for (size_t i = 0; i < VEC_SIZE; i++) {
		if (i == VEC_SIZE - 1) cout << "^ ";
		else cout << char(i+65) << " ";
		for (size_t j = 0; j < VEC_SIZE; j++) {
			if (i == VEC_SIZE) break;
			cout << letter_occurence_map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

string createName(vector<vector<int>> letter_occurence_map, int count) {
	string retval;

	//this will be our starting letter
	int roll = rand() % count;
	for (unsigned int row = 0; row < VEC_SIZE - 1; row++) {

	}
	return retval;

}

void parseFile(vector<vector<int>> &letter_occurence_map, const string &filename, int &names_read) {
	ifstream ins(filename);
	if (!ins) {
		cout << "Error loading file.\n";
		exit(EXIT_FAILURE);
	}
	if (ins.peek() == EOF) {
		cout << "Error, file was empty.\n";
		exit(EXIT_FAILURE);
	}
	const unsigned int NEW_LINE_DEC_VALUE = 10;
	int prev_letter = '^'; // start of line
	int index_pos_of_letter = 0;
	int index_pos_of_prev_letter = 0;
	while (ins) {
		int c = toupper(ins.get());
		if (!ins)
			break;
		if (c >= 65 && c <= 90){ // normal uppercase letters
			index_pos_of_letter = c - 65;
			if (prev_letter == '^') // Start of string
				index_pos_of_prev_letter = VEC_SIZE-1;
			else
				index_pos_of_prev_letter = prev_letter - 65;
			assert(index_pos_of_letter >= 0 && index_pos_of_letter < (int)VEC_SIZE);
			assert(index_pos_of_prev_letter >= 0 && index_pos_of_prev_letter < (int)VEC_SIZE);
			letter_occurence_map.at(index_pos_of_prev_letter).at(index_pos_of_letter) += 1;
			prev_letter = c;
			if (ins.peek() == EOF) { // special case for EOF
				index_pos_of_prev_letter = prev_letter - 65;
				letter_occurence_map.at(index_pos_of_prev_letter).at(VEC_SIZE-1) += 1;
				names_read++;
			}
		}
		if (c == NEW_LINE_DEC_VALUE) { // new line
			if (prev_letter == '^') continue; // if the prev_letter is the start and the first read letter is a new line, its not a word.
			index_pos_of_prev_letter = prev_letter - 65;
			letter_occurence_map.at(index_pos_of_prev_letter).at(VEC_SIZE-1) += 1;
			prev_letter = '^';
			names_read++;
		}
	}
}

int main() {
	vector<vector<int>> letter_occurence_map_first_names(VEC_SIZE, vector<int> (VEC_SIZE));
	cout << "Please enter a filename of firstnames to open:\n";
	string filename;
	cin >> filename;
	int first_names_read = 0;
	parseFile(letter_occurence_map_first_names, filename, first_names_read);
	cout << filename << " successfully loaded. First Names read: " << first_names_read << endl;
	cout << "Please enter a filename of lastnames to open:\n";
	cin >> filename;
	vector<vector<int>> letter_occurence_map_last_names(VEC_SIZE, vector<int> (VEC_SIZE));
	int last_names_read = 0;
	parseFile(letter_occurence_map_last_names, filename, last_names_read);
	cout << filename << " successfully loaded. Last Names read: " << last_names_read << endl;
	cout << "1. Print Adjacency Matrices\n";
	cout << "2. Generate Random Names\n";
	int choice = 1;
	cin >> choice;
	if (!cin or choice < 1 or choice > 2) die();
	if (choice == 1) {
		printVector(letter_occurence_map_first_names);
		printVector(letter_occurence_map_last_names);
	}
	if (choice == 2) {
		cout << "Please enter random seed:\n";
		unsigned int seed = 0;
		cin >> seed;
		if (!cin) die();
		srand(seed);
		cout << "How many random names do you want to generate?\n";
		int random_names_desired = 0;
		cin >> random_names_desired;
		if (!cin or random_names_desired < 0) die();
		while (random_names_desired) {
			string random_first_name = createName(letter_occurence_map_first_names, first_names_read);
			string random_last_name = createName(letter_occurence_map_last_names,first_names_read);
			cout << random_first_name << " " << random_last_name << endl;
			random_names_desired--;
		}
	}
}
