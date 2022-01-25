//Student 1 Name:
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
using namespace std;

const int RED = 0, GREEN = 1, BLUE = 2;
//YOU: Write your own filter here - delete the demo code or modify it to suit your purposes
void filter1(vector<vector<vector<int>>> &vec) {
	//Get the number of rows, columns, and colors in this 3D vector
	size_t rows = vec.size();
	if (!rows) exit(1);
	size_t cols = vec.at(0).size();
	if (!cols) exit(1);
	size_t colors = vec.at(0).at(0).size();
	if (!colors) exit(1);

	//Do the image filtering on every row and column in this image...
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			//DEMO CODE BEGIN
			//The demo code here will either sepia tone or yellowize the image, depending on which one you comment out
			/*
			//Simple Example - Make the image more yellowish
			vec.at(i).at(j).at(RED) *= 1.3; //Increase red value at every point by 50%
            vec.at(i).at(j).at(GREEN) *= 1.2; //Increase green at every point by 20%
            vec.at(i).at(j).at(BLUE) *= 0.8; //Reduce blue by 20%
			*/

			//Complex Example - Do sepia toning
			//Get the red, green and blue values at row i, col j:
			int r = vec.at(i).at(j).at(RED); //Bounds check with .at the first time
			int g = vec[i][j][GREEN]; //Skip bounds check for speed
			int b = vec[i][j][BLUE];
			//These magic numbers do sepia toning
			vec[i][j][RED]   = r*0.393 + g*0.769 + b*0.189;
			vec[i][j][GREEN] = r*0.349 + g*0.686 + b*0.168;
			vec[i][j][BLUE]  = r*0.272 + g*0.534 + b*0.131;
			//DEMO CODE END
		}
	}
}
