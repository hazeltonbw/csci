//Student 3 Name:
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
using namespace std;

const int RED = 0, GREEN = 1, BLUE = 2;

//YOU: Write your own filter here - delete the demo code or modify it to your purposes
void filter3(vector<vector<vector<int>>> &vec) {
    size_t rows = vec.size();
    if (!rows) exit(1);
    size_t cols = vec.at(0).size();
    if (!cols) exit(1);
    size_t colors = vec.at(0).at(0).size();
    if (!colors) exit(1);

    const double diag_length = hypot(rows/2.0,cols/2.0); //How many pixels is the diagonal from the center of the image to a corner?
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            //DEMO CODE BEGIN
            for (int k = 0; k < colors; k++) {
                vec.at(i).at(j).at(k) /= 2; //Darken by 50%
            }
            //DEMO CODE END
        }
    }
}
