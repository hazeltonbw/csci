#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main() {
	srand(time(NULL));
	ofstream outs("custom_map.dat");
	int rows = rand() % 100 + 100;
	int cols = rand() % 200 + 100;
	outs << cols << " " << rows << endl;
	for (int col = 0; col < cols; col++) {
		for (int row = 0; row < rows; row++) {
			int random_number = rand() % 2000;
			if (random_number >= 42 && random_number <= 69) random_number *= -1;
			outs << random_number << " ";
		}
		outs << endl;
	}
}
