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


// This program implements the mountain paths assignment in C++. See the README.md for a
// detailed description

// function prototypes
ColorGrid *getImage (int *img_arr, int imgWidth, int imgHeight, int maxVal);
int *readData (int *imgWidth, int *imgHeight, int *maxVal, string file_name);
void findPath_Greedy(int *img_arr, int imgWidth, int imgHeight, int startRow, int maxVal);
void findPath_Djikstra(int *elev_data, int imgWidth, int imgHeight, int startRow, int startCol, int endRow, int endCol);

bool stringCorrectFileExtension(string &str) {
	return str.find(".dat") != string::npos;
}

int main(int argc, char **argv) {
	int bridges_project_id = 69;
	const string bridges_username = "0513127";
	const string bridges_api_key  = "1084964851347";
	// parse command line arguments
	// argument 2 is input file
	string filename = "colorado1.dat";
	if (argc >= 2) {
		filename = argv[1]; //This is how you read a command line parameter
		if (filename == "--help" or filename == "-h") {
			cout << "Usage: ./a.out filename.dat bridges_project_id" << endl;
			exit(0);
		}
		if (!stringCorrectFileExtension(filename)) {
			cout << "Bad filename! Filename must end with .dat\n";
			exit(EXIT_FAILURE);
		}
	}
	if (argc >= 3) {
		string bridges_id;
	    bridges_id = argv[2];
		for (int i = 0; i < bridges_id.size(); i++) {
			if (!isdigit(bridges_id[i])) {
				cout << "Third argument needs to be a number. Ex: ./a.out filename.dat 50\tThis will be your project ID for bridges.\n";
				exit(EXIT_FAILURE);
				}
		}
		bridges_project_id = atoi(argv[2]);
	}

	//Delete this line once you get registered on BRIDGES
//	static_assert(false,"You must register on BRIDGES and get your own usernsme and API key.");

	// bridges object initialization
	Bridges bridges(bridges_project_id, bridges_username, bridges_api_key);

	// read input elevation data
	int width, height, maxVal;
	int *elev_data;

	elev_data = readData(&width, &height, &maxVal, filename);

	// set title
	//YOU: Change this to "Mountain Paths - Dijkstra's"

	// parse filename given, add to title
	string title = "Mountain Paths - Dijkstra's - ";
	for (int i = 0; i < filename.size(); i++) {
		if (filename[i] == '.') break; // we've reached the filetype extension, quit.
		else if (i == 0) title += toupper(filename[i]);
		else if (filename[i] == '_') {
			title += ' ';
			int next_character_index = i+1;
			if (next_character_index < filename.size()) {
				title += toupper(filename[next_character_index]);
				i++;
			}
		}
		else if (isdigit(filename[i])) {
			// Separate numbers from text... ex: colorado1 will become Colorado 1
			title += ' ';
			title += filename[i];
		}
		else title += filename[i];
	}
	bridges.setTitle(title);

	//WRK - Added this section
	//Get starting row and column - the greedy algorithm only needs starting row,
	// but you will use the two locations for doing Dijkstra's
	int startRow = 0, startCol = 0, endRow = 0, endCol = 0;
	cout << "Rows: " << height << "\tCols: " << width << endl;
	cout << "Please enter starting row and col:\n"; //Only starting row is used for greedy mode
	cin >> startRow >> startCol;
	cout << "Please enter ending row and col:\n"; //Neither of these is used in greedy mode
	cin >> endRow >> endCol;

	//YOU: Replace the greedy algorithm with Dijkstra's or A* between the starting and ending points
	//YOU: Look at how findPath does it's think in regards to converting between a 2D location and a 1D array, as well as how it marks the final path by changing the elevation to -1 along the path
	// find path by applying a greedy algorithm from the left side of the screen to the right
	//void findPath_Djikstra(int *elev_data, int imgWidth, int imgHeight, int startRow, int startCol, int endRow, int endCol, int maxVal){
	findPath_Djikstra(elev_data, width, height, startRow, startCol, endRow, endCol);

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
	if (!infile.good()) { // Not good... file doesn't exist.
		cout << "File doesn't exist! Exiting...\n";
		exit(EXIT_FAILURE);
	}
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

		if (val < 0) val = -5;
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
		else if (pixel_val <= -2.) {// below sea level == WATER, usually... so color it blue.
			// this is the path drawn in yellow across the image
			cg->set(j, k, Color(15, 20, 40)); // blue
//			cg->set(j, k, Color(255, 0, 255)); // yellow
		}
		else {
			// scale value to be within 0-255, for r,g,b range
			gray = (int) (pixel_val*255./maxVal);
			if (gray <= 30 && gray >= 15)
										// Add 30% green for greenery effect
				cg->set(j, k, Color(gray, gray*1.30, gray));
			else if (gray < 200 && gray > 30) {
										// Remove 6% green, 12% blue to make mountains pop
				cg->set(j, k, Color(gray, gray*.94, gray*.88));
//				cg->set(j, k, Color(gray, gray - gray*.06, gray - gray*.12));
			}
			else cg->set(j, k, Color(gray, gray, gray));
		}
	}
	return cg;
}

void findPath_Djikstra(int *elev_data, int imgWidth, int imgHeight, int startRow, int startCol, int endRow, int endCol){

	if (startRow < 0 or startRow >= imgHeight or startCol < 0 or startCol >= imgWidth) {
		cout << "Invalid starting row or column.\n"; //WRK Let them know
		return;
	}

	int sum_of_coord_change = 0;
	int elev_data_from = 0;
	int elev_data_to = 0;
	Tile starting_tile(startCol, startRow, -1, -1, 0);
	priority_queue<Tile, vector<Tile>, Tile_Comp> to_process;
	to_process.push(starting_tile);
	unordered_set<Tile> processed;
	Tile temp = {-1,-1,-1,-1,0};
	while (!to_process.empty()){
		temp = to_process.top();
		int col = temp.x;
		int row = temp.y;
		if (col == endCol and row == endRow) break; // if we reached the end break
		to_process.pop();
		if (processed.find(temp) != processed.end()) continue; // if its in the process list
		processed.insert(temp);
		for (int i = col - 1; i <= col + 1; i++) {
			if (i < 0 or i >= imgWidth) continue;
			for (int j = row - 1; j <= row + 1; j++) {
				if (j < 0 or j >= imgHeight) continue;
				if (i == col && j == row) continue;
				if (i == temp.from_x && j == temp.from_y) continue;
				elev_data_from = elev_data[row*imgWidth + col];
				elev_data_to = elev_data[j*imgWidth + i];
				if (elev_data_from < 0) {
					elev_data[row*imgWidth + col] = -2;
					continue;
				}
				if (elev_data_to < 0) {
					elev_data[j*imgWidth + i] = -2;
					continue;
				}

				Tile new_tile(i, j, col, row, 0);
				sum_of_coord_change = abs(col - i) + abs(row - j);
				if (sum_of_coord_change == 1) // lateral
					new_tile.distance = temp.distance + 1840 + (20 * abs(elev_data_from - elev_data_to));
				if (sum_of_coord_change == 2) // diagonal
					new_tile.distance = temp.distance + 2601 + (20 * abs(elev_data_from - elev_data_to));
				if (!processed.count(new_tile))
					to_process.push(new_tile);
			}
		}
	}
	cout << "Found the exit!!!! BaCKTRACK TIME!!!!!\n";
	cout << "Distance to end tile: " << temp.distance << endl;
	while (1) {
		elev_data[temp.y*imgWidth + temp.x] = -1;
		temp.x = temp.from_x;
		temp.y = temp.from_y;
		if (temp.x == -1 or temp.y == -1) break;
		temp = *processed.find(temp);
	}
}
