#include "Bridges.h"
#include <queue>
#include "tile.h"
#include "ColorGrid.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
using namespace std;
using namespace bridges;

typedef priority_queue<Tile, vector<Tile>, Tile_Comp> Tile_pq;
// This program implements the mountain paths assignment in C++. See the README.md for a
// detailed description

// function prototypes
ColorGrid *getImage (int *img_arr, int imgWidth, int imgHeight, int maxVal);
int *readData (int *imgWidth, int *imgHeight, int *maxVal, string file_name);
void findPath_Greedy(int *img_arr, int imgWidth, int imgHeight, int startRow, int maxVal);
void findPath_Djikstra(int *elev_data, int imgWidth, int imgHeight, int startRow, int startCol, int endRow, int endCol, int maxVal);

int main(int argc, char **argv) {
	const int bridges_project_id = 69;
	const string bridges_username = "0513127";
	const string bridges_api_key  = "1084964851347";

	//Delete this line once you get registered on BRIDGES
//	static_assert(false,"You must register on BRIDGES and get your own usernsme and API key.");

	// bridges object initialization
	Bridges bridges(bridges_project_id, bridges_username, bridges_api_key);

	// read input elevation data
	int width, height, maxVal;
	int *elev_data;

	// parse command line arguments
	// argument 2 is input file
	string filename = "./colorado1.dat";
//	string filename = "dummy.dat";
	if (argc >= 2) filename = argv[1]; //This is how you read a command line parameter
	elev_data = readData(&width, &height, &maxVal, filename);

	// set title
	//YOU: Change this to "Mountain Paths - Dijkstra's"
	bridges.setTitle("Mountain Paths - Dijkstra's");


	//WRK - Added this section
	//Get starting row and column - the greedy algorithm only needs starting row,
	// but you will use the two locations for doing Dijkstra's
	int startRow = 0, startCol = 0, endRow = 0, endCol = 0;
	cout << "Please enter starting row and col:\n"; //Only starting row is used for greedy mode
	cin >> startRow >> startCol;
	cout << "Please enter ending row and col:\n"; //Neither of these is used in greedy mode
	cin >> endRow >> endCol;

	//YOU: Replace the greedy algorithm with Dijkstra's or A* between the starting and ending points
	//YOU: Look at how findPath does it's think in regards to converting between a 2D location and a 1D array, as well as how it marks the final path by changing the elevation to -1 along the path
	// find path by applying a greedy algorithm from the left side of the screen to the right
	//void findPath_Djikstra(int *elev_data, int imgWidth, int imgHeight, int startRow, int startCol, int endRow, int endCol, int maxVal){
	findPath_Djikstra(elev_data, width, height, startRow, startCol, endRow, endCol, maxVal);

	// get the path written into a color grid for visualization
	//YOU: Change the path color to red
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
			// this is the path drawn in yellow across the image
			cg->set(j, k, Color(255, 0, 0)); // red
//			cg->set(j, k, Color(255, 0, 255)); // yellow
		}
		else if (pixel_val == -2.) {// below sea level == WATER, usually... so color it blue.
			// this is the path drawn in yellow across the image
			cg->set(j, k, Color(0, 0, 255)); // blue
//			cg->set(j, k, Color(255, 0, 255)); // yellow
		}

		else {
			// scale value to be within 0-255, for r,g,b range
			gray = (int) (pixel_val*255./maxVal);
			cg->set(j, k, Color(gray, gray, gray));
		}
	}
	return cg;
}
void findPath_Djikstra(int *elev_data, int imgWidth, int imgHeight, int startRow, int startCol, int endRow, int endCol, int maxVal){

	if (startRow < 0 or startRow >= imgHeight or startCol < 0 or startCol >= imgWidth) {
		cout << "Invalid starting row or column.\n"; //WRK Let them know
		return;
	}

	const int MAPSIZE = imgWidth * imgHeight;
	Tile starting_tile(startCol, startRow, -1, -1, 0);
	Tile_pq to_process;
	to_process.push(starting_tile);
	unordered_set<Tile> processed;
	while (!to_process.empty())
	{
		const Tile &temp = to_process.top();
		int col = temp.x;
		int row = temp.y;
		// cout << "Row: " << row << "\tCol: " << col << endl;
		// cout << temp.x << " " << temp.y << endl;


		for (int i = col - 1; i < col + 2; i++) {
			if (i < 0 or i >= imgWidth) continue;
			for (int j = row - 1; j < row + 2; j++) {
				if (j < 0 or j >= imgHeight or i == col && j == row)
					continue;
//				else if (i == temp.from_x && j == temp.from_y)
//					continue;
				else {
					// cout << "i: " << i << "\tj: " << j << endl;
					// cout << elev_data[i*imgWidth + j] << endl;

					// cout << i*imgWidth + j << endl;
					Tile new_tile(i, j, col, row, 0);
					int sum_of_coord_change = abs(col - i) + abs(row - j);
					if (sum_of_coord_change == 1) { // lateral
						int elev_data_from = elev_data[row*imgWidth + col];
						int elev_data_to = elev_data[j*imgWidth + i];
						new_tile.distance = temp.distance + 1840 + (20 * abs(elev_data_from - elev_data_to));
					}
					else if (sum_of_coord_change == 2) {// diagonal
						int elev_data_from = elev_data[row*imgWidth + col];
						int elev_data_to = elev_data[j*imgWidth + i];
						new_tile.distance = temp.distance + 2601 + (20 * abs(elev_data_from - elev_data_to));
					}
					else{
						cout << "Something went wrong.\n";
						cout << "Col - i = " << col-i << "\tRow - j = " << row-j << endl;
						exit(1);
					}
					// cout << new_tile << endl;
					if (!processed.count(new_tile))  {
						to_process.push(new_tile); // Creates and pushes a new tile
						//cout << new_tile << endl;
					}
				}
			}
		}
		processed.insert(to_process.top());
		to_process.pop();
	}
	// cout << temp << endl;
	//for (const auto& elem: processed){
	//	elev_data[elem.x*imgWidth + elem.y] = -1;
	//	cout << elem << endl;
	//}
	// After all of that, change the elev_data of the path to -1 to draw a line.
	Tile tile(endCol, endRow, -1, -1, 0);
	tile = *processed.find(tile);
	elev_data[tile.x*imgWidth + tile.y] = -1;
	while (1) {
		tile.x = tile.from_x;
		tile.y = tile.from_y;
		tile = *processed.find(tile);
		elev_data[tile.x*imgWidth + tile.y] = -1;
		if (tile.from_x == -1) {
			break;
		}
	}

}

// determines the least effort path through the mountain starting a point on
// the left edge of the image
void findPath_Greedy(int *elev_data, int imgWidth, int imgHeight, int startRow, int maxVal) {

	if (startRow < 0 || startRow >= imgHeight) {
		cout << "Invalid starting row.\n"; //WRK Let them know
		return;
	}

	int col = 0, row = startRow;
	int pix_addr = startRow*imgWidth + col;

	while (col < imgWidth-2) {
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
}
