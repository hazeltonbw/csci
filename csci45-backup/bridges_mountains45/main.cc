#include "Bridges.h"
#include "ColorGrid.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
using namespace std;
using namespace bridges;

// function prototypes
ColorGrid *getImage (int *img_arr, int imgWidth, int imgHeight, int maxVal);
int *readData (int *imgWidth, int *imgHeight, int *maxVal, string file_name);
extern "C" {
	void findPath(int *img_arr, int imgWidth, int imgHeight, int startRow, int maxVal);
	void print(int *img_arr, int imgWidth, int imgHeight) {
		for (int i = 0; i < imgWidth; i++) {
			for (int j = 0; j < imgHeight; j++) {
				cout << img_arr[i*imgWidth+j]<< " " ;
			}
			cout << endl;
		}
	}
}

int main(int argc, char **argv) {
	int bridges_project_id = 69420;
    string bridges_username = "0513127";
    string bridges_api_key  = "1084964851347";

	// bridges object initialization
	Bridges bridges(bridges_project_id, bridges_username, bridges_api_key);

	// read input elevation data
	int width, height, maxVal;
	int *elev_data;

	// parse command line arguments
	// argument 2 is input file
	string filename = "./colorado1.dat";
	//string filename = "./test.dat";
	if (argc >= 2) filename = argv[1]; //This is how you read a command line parameter
	elev_data = readData(&width, &height, &maxVal, filename);

	//WRK - Added this section
	//Get starting row and column - the greedy algorithm only needs starting row,
	int startRow = 0;
	cout << "Please enter starting row:\n"; //Only starting row is used for greedy mode
	cin >> startRow;

	// set title
	bridges.setTitle("Mountain Paths "s + filename + " - Starting Row: " + to_string(startRow));

	//YOU: Look at how findPath does it's think in regards to converting between a 2D location and a 1D array, as well as how it marks the final path by changing the elevation to -1 along the path
	// find path by applying a greedy algorithm from the left side of the screen to the right
	findPath (elev_data, width, height, startRow, maxVal);
	
	// get the path written into a color grid for visualization
	//YOU: Change the path color to blue
	ColorGrid *cg = getImage(elev_data, width, height, maxVal);

	// visualize
	bridges.setDataStructure(cg);
	bridges.visualize();

	delete cg; //WRK Fix memory leak in BRIDGES
	delete[] elev_data; //WRK Ditto
}

int *readData(int *width, int *height, int *maxVal, string file_name) {

	ifstream infile(file_name.c_str());

	// read header 
	int max = 0, w, h, val;
	infile >> w >> h;

	*width = w; *height = h;

	// allocate space for the input data
	// we will use a 1D array
	int size = w*h;
	int *elev_data = new int[size];
	assert(elev_data); //WRK

	// read the elevation data
	for (int k = 0; k < size; k++) {
		infile >>  val;

		// update the max val
		max = (val > max) ? val : max;
	
		// store  in elevation array
		elev_data[k] = val;
	}
	// record the max value
	*maxVal = max;

	return elev_data;
}

// takes in the processed elevation data and returns a color grid for 
// visualization using BRIDGES
ColorGrid *getImage(int *elev_data, int width, int height, int maxVal) {
	// create color grid
	ColorGrid *cg = new ColorGrid(height, width);

	float pixel_val;
	int n = 0, gray;

	// load the elevation data
	for (int j = 0; j < height; j++)
	for (int k = 0; k < width; k++) {
		pixel_val = (float) elev_data[n++];
		if (pixel_val == -1.) {
			// this is the path drawn in purple across the image
			cg->set(j, k, Color(255, 0, 255));
		}
		else {
			// scale value to be within 0-255, for r,g,b range
			gray = (int) (pixel_val*255./maxVal);	
			cg->set(j, k, Color(gray, gray, gray));
		}
	}
	return cg;
}

// determines the least effort path through the mountain starting a point on
// the left edge of the image
//YOU: Rewrite this in ARM32 assembly
/*
void findPath(int *elev_data, int imgWidth, int imgHeight, int startRow, int maxVal) {
	
	if (startRow < 0 || startRow >= imgHeight) {
		cout << "Invalid starting row.\n"; //WRK Let them know
		return;
	}

	int col = 0, row = startRow; 
	int pix_addr = startRow*imgWidth + col;

	while (col < imgWidth-1) {
		// hold neighbors in array
		int neighb[3] = {0, 0, 0};

		// compute 2D address of pixel from 1D address
		row = pix_addr/imgWidth;
		col = pix_addr - row*imgWidth;
		int top_right = pix_addr - imgWidth + 1;
		int right = pix_addr + 1;
		int bottom_right = pix_addr + imgWidth + 1;
		int cnt;

		// color the pixel, its in the path
		elev_data[pix_addr] = -1; 

		// deal with boundary cases first
		if (row == 0) { 
			// must  go right or down
			cnt = 2;
			neighb[0] = right; neighb[1] = bottom_right;
		}
		else if (row == imgHeight-1){ 
			// must go right or up
			cnt = 2;
			neighb[0] = right; neighb[1] = top_right;
		}
		else { 	
			// general case
			// check the 3 right neighbors, make greedy decision 
			cnt = 3;
			neighb[0] = top_right; neighb[1] = right; neighb[2] = bottom_right;
		}

		// compute differences with right neighbors
		int min = maxVal;
		int diff[3];
		for (int k = 0; k < cnt; k++)  {
			int d = elev_data[pix_addr] - elev_data[neighb[k]];
			diff[k] = (d < 0) ? -d : d;
		}
		// choose pixe with the smallest difference
		switch (cnt) {
			case 2: 
				pix_addr =  (diff[0] <= diff[1]) ? neighb[0] : neighb[1];
				break;
			case 3:
				if (diff[0] < diff[1] && diff[0] < diff[2])
					pix_addr = neighb[0];
				else 
					if (diff[1] < diff[0] && diff[1] < diff[2])
						pix_addr = neighb[1];
				else 
					if (diff[2] < diff[0] && diff[2] < diff[1])
						pix_addr = neighb[2];
				else if ((diff[0] == diff[1]) || (diff[1] == diff[2]))
						pix_addr = neighb[1];
				else { 
					double val = drand48();
					pix_addr = (val < 0.5) ? neighb[0] : neighb[2];
			}
		}
		col++;
	}
	elev_data[pix_addr] = -1; 
}
*/
