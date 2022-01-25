#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

class Rectangle {
	int x_min, y_min, x_max, y_max, treasure_value;
	public:
	Rectangle(int x_min, int y_min, int x_max, int y_max, int treasure_value) {
		this->x_min = x_min;
		this->y_min = y_min;
		this->x_max = x_max;
		this->y_max = y_max;
		this->treasure_value = treasure_value;
	}
};

[[noreturn]]
void die() {
	cout << "BAD INPUT!\n";
	exit(EXIT_FAILURE);
}

int main() {
	cout << "Welcome to Buried Treasure!\n";
	//Phase 1 - Input Phase
	string filename;
	printf("Please enter the filename to read the treasure data from:\n");
	cin >> filename;
	ifstream ins(filename);
	if (!ins) die();
	//YOU: Read from this file into a vector of Rectangles or whatever you want to call it
	// int min x, min y, max x, max y, treasure_value
	int x_min = 0, y_min = 0, x_max = 0, y_max = 0, treasure_value = 0;
	vector<Rectangle> vec;
	while (1) {
		ins >> x_min >> y_min >> x_max >> y_max >> treasure_value;
		if (!ins) break;
		vec.push_back({x_min, y_min, x_max, y_max, treasure_value});
	}

	//Phase 2 - Movement Phase
	//YOU: Start the player at 0,0 and let them move around until they choose to dig, at which point they get treasure or not
	int money = 0;
	int x_loc = 0, y_loc = 0, digs_left = 5;
	while (1) {
		printf("You are at location (%i,%i). You have %i digs left. Do you wish to (D)ig or move (N)orth, move (S)outh, move (W)est or move (E)ast?", x_loc, y_loc, digs_left);
		string input;
		cin >> input;
		if (toupper(input.at(0)) == 'D') {

		}
		else if (toupper(input.at(0)) == 'N') {

		}
		else if (toupper(input.at(0)) == 'S') {

		}
		else if (toupper(input.at(0)) == 'W') {

		}
		else if (toupper(input.at(0)) == 'E') {

		}
		else {
			die();
		}
	}
	//Phase 3 - Output Phase
	cout << "Your final total is: " << money << " dollars!\n";
}
