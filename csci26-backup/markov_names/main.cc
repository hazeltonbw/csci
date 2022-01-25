#include <iostream>
#include <numeric>
#include <assert.h>
#include <unordered_map>
#include <vector>
#include <fstream>
using namespace std;
const unsigned int VEC_SIZE = 27;
const unsigned int NEW_LINE_DEC_VALUE = '\n';
const int STARTING_ALPHA_DEC = 'A'; //uppercase alpha
const int ENDING_ALPHA_DEC = 'Z'; //uppercase alpha

void die() {cout << "BAD INPUT!\n"; exit(EXIT_FAILURE);}
void uppercasify(string &s) { for (char &c: s) c = toupper(c); }
void printVector(const vector<vector<int>> &letter_occurence_map) {
	// HEADER [A-Z] $
	// from 'A' to '[' which is 1 past 'Z',
	// create the header for the 2d matrix.
	// when i == '[' we will instread print '$'
	// ex:  A B C D E F G H I J K L M N O P Q R S T U V W X Y Z $
	for (int i = STARTING_ALPHA_DEC; i <= ENDING_ALPHA_DEC + 1; i++) {
		if (i == STARTING_ALPHA_DEC) cout << "  ";
		if (i == ENDING_ALPHA_DEC + 1) cout << "$";
		else cout << char(i) << " ";
	}
	cout << endl;

	// print the values stored in the vector
	for (size_t i = 0; i < VEC_SIZE; i++) {
		if (i == VEC_SIZE - 1) cout << "^ ";
		else cout << char(i+STARTING_ALPHA_DEC) << " ";
		for (size_t j = 0; j < VEC_SIZE; j++) {
			cout << letter_occurence_map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

string createName(const vector<vector<int>> &letter_occurence_map, int count) {
	string retval;
	const int END_LINE_INDEX = 26;

	int index_of_curr_char = END_LINE_INDEX; // start at beginning index, which happens to have the same index number as end line
	while(1) {
		if (count == 0) break; // no division by 0
		int roll = rand() % count;
//		cout << "You rolled: " << roll << endl;
		for (size_t i = 0; i < letter_occurence_map.size(); i++) {
			roll -= letter_occurence_map.at(index_of_curr_char).at(i);
			if (roll < 0){
				if (i == END_LINE_INDEX) return retval;
				int char_dec_value = i + STARTING_ALPHA_DEC;
				retval += char(char_dec_value);
				count = accumulate(letter_occurence_map.at(i).begin(), letter_occurence_map.at(i).end(), 0);
				index_of_curr_char = i;
				break;
			}
		}
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
	int prev_letter = '^'; // start of line
	int index_pos_of_letter = 0;
	int index_pos_of_prev_letter = 0;
	while (ins) {
		int c = toupper(ins.get());
		if (!ins)
			break;
		if (c >= STARTING_ALPHA_DEC && c <= ENDING_ALPHA_DEC){ // normal uppercase letters
			index_pos_of_letter = c - STARTING_ALPHA_DEC;
			if (prev_letter == '^') // Start of string
				index_pos_of_prev_letter = VEC_SIZE-1;
			else
				index_pos_of_prev_letter = prev_letter - STARTING_ALPHA_DEC;
//			assert(index_pos_of_letter >= 0 && index_pos_of_letter < (int)VEC_SIZE);
//			assert(index_pos_of_prev_letter >= 0 && index_pos_of_prev_letter < (int)VEC_SIZE);
			letter_occurence_map.at(index_pos_of_prev_letter).at(index_pos_of_letter) += 1;
			prev_letter = c;

			// special case for EOF
			// some files wouldn't have a newline at the end,
			// so if we have processed some data and reach EOF,
			// treat it as a newline.
			// the next iteration of the while loop will break at if (!ins) after reaching EOF
			if (ins.peek() == EOF) {
				index_pos_of_prev_letter = prev_letter - STARTING_ALPHA_DEC;
				letter_occurence_map.at(index_pos_of_prev_letter).at(VEC_SIZE-1) += 1;
				names_read++;
			}
		}
		if (c == NEW_LINE_DEC_VALUE) { // new line
			// if the prev_letter is the start and the first read letter is a new line, its not a word. skip it
			if (prev_letter == '^') continue;

			//else, we are at the end of a word, add the occurence to the map and reset prev_letter to '^' for the next word
			//increment names_read by 1
			index_pos_of_prev_letter = prev_letter - STARTING_ALPHA_DEC;
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
			string random_last_name = createName(letter_occurence_map_last_names,last_names_read);
			cout << random_first_name << " " << random_last_name << endl;
			random_names_desired--;
		}
	}
}
