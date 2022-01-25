#include <iostream>
#include <vector>
using namespace std;

int lowestElement(vector<vector<int>> &vec, int x, int y) {
	int retval = vec[x][y];
	int min_row = x - 1 < 0 ? 0 : x - 1;
	int min_col = y - 1 < 0 ? 0 : y - 1;
	int max_row = x + 2 > (int)vec[0].size() ? vec[0].size(): x + 2;
	int max_col = y + 2 > (int)vec.size() ? vec.size(): y + 2;
	for (int i = min_row; i < max_row; i++)
		for (int j = min_col; j < max_col; j++) {
			if (i == x && j == y) continue; // We don't need to test the value passed into the function, it's already set as the lowest above
//			cout << "Currently testing number " << vec[i][j] << " < " << retval << " ??? \t" << boolalpha << (bool)(vec[i][j] < retval) << endl;
			if (vec[i][j] < retval) retval = vec[i][j];
		}

//	cout << "Testing from numbers from row " << min_row << " to " << max_row - 1 << endl;
//	cout << "Testing from numbers from col " << min_col << " to " << max_col - 1 << endl;

	return retval;
}


/*
int lowestElement(std::vector<std::vector<int>> vec, int x, int y) {
	int retval = vec[x][y];
	for (int i = x - 1; i < x + 2; i++) {
		for (int j = y - 1; j < y + 2; j++) {
			if (i < 0 or j < 0 or i >= vec.size() or j >= vec.size() or (i == x && j == y))
				continue;
			if (vec[i][j] < retval) retval = vec[i][j];
		}
	}
	return retval;
}
*/

void printVector(vector<vector<int>> &vec, int x, int y) {
	for (size_t i = 0; i < vec.size(); i++) {
		for (size_t j = 0; j < vec[i].size(); j++) {
			if (j < vec[i].size()) {
				if ((int)i == x && (int)j == y){
					cout << "*" << vec[i][j] << "*\t";
				}
				else {
				cout << vec[i][j] << "\t";
				}
			}
		}
		cout << endl;
	}
}

int main() {
	vector<vector<int>> vec{{1,2,3},
							{4,5,6},
						   	{7,8,9}};
	vector<vector<vector<int>>> vec2; // Yo dawg I heard you like vectors so I put a vector in your vector of vectors


	int x = 1, y = 1;

	printVector(vec, x, y);
	// Find lowest neighbor of [1][1] , which is the int value 5. It should return 1.
	cout << "The lowest neighboring element of (" << x << ", " << y << ") is: ";
	cout << lowestElement(vec, x, y) << endl << endl;


	vec = {
		   {-505,40134,14001},
		   {-13,150,50}      ,
		   {-530,143,123}
	};
	printVector(vec, x, y);
	cout << "The lowest neighboring element of (" << x << ", " << y << ") is: ";
	cout << lowestElement(vec, x, y) << endl << endl;




	x = 1; y = 3;
	vec = {
		   {-505,40134,14001, -15013513},
		   {-13,150,50, -13513409}      ,
		   {-530,143,123,-3515911}      ,
		   {135135,15143,127983,-343515911}

	};
	printVector(vec, x, y);
	cout << "The lowest neighboring element of (" << x << ", " << y << ") is: ";
	cout << lowestElement(vec, x, y) << endl << endl;
}
