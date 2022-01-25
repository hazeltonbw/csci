#include "Bridges.h"
#include "ColorGrid.h"
#include "/public/read.h"   //Kerney's input thing
#include "/public/colors.h" //Kerney's color thing
#include <cstdlib>
#include <climits>
#include <vector>
#include <sstream>
using namespace std;
using namespace bridges;

vector<vector<int>> load_data(const string &filename); //Loads data from a file
void print_data(const vector<vector<int>> &heat_data); //Prints the vector to the screen
void heat_transfer(vector<vector<int>> &heat_data); //Does the physics of heat transfer
void kerney_visualize(const vector<vector<int>> &heat_data); //Kerney will draw your vector for you
ColorGrid *getImage(const vector<vector<int>> &heat_data); //Returns a ColorGrid * that Bridges will visualize

//Main is done for you
int main() {
	string bridges_username = "0513127";
	string bridges_api_key  = "1084964851347";

	cout << "Please enter the project id (if you use the same as an old one it will overwrite it on BRIDGES):\n";
	const int bridges_project_id = read(); //Reads an int from cin

	// bridges object initialization
	Bridges bridges(bridges_project_id, bridges_username, bridges_api_key);

	cout << "Please enter a heat file to open:\n";
	const string filename = read();

	vector<vector<int>> heat_data = load_data(filename); //Load the data from filename into heat_data

	//Print the before and after
	cout << "Data before running heat transfer:\n";
	print_data(heat_data); //Prints the data you loaded

	cout << "How many iterations do you want to run it for?\n";
	int iterations = read(); //How many times to run the heat transfer function
	if (iterations <= 0) exit(0);

	//Main loop
	cout << '';
	clearscreen();
	set_cursor_mode(false);
	for (int i = 0; i < iterations; i++) {
		heat_transfer(heat_data); //Runs your code
		kerney_visualize(heat_data); //Visualizes it
	}
	set_cursor_mode(true);

	cout << "\nData after running heat transfer:\n";
	print_data(heat_data); //Prints the data after running heat transfer N times

	// debugging
	/*
	for (int i = 0; i < iterations; i++) {
		heat_transfer(heat_data);
		print_data(heat_data);
	}
	*/

	//Send data to BRIDGES
	ColorGrid *cg = getImage(heat_data); //Allocates memory
	bridges.setTitle(bridges_username + "'s heat: " + filename);
	bridges.setDataStructure(cg);
	bridges.visualize();
	delete cg;
}

//Read data from a file into a 2D vector that you return
vector<vector<int>> load_data(const string &filename) {
	ifstream infile(filename);
	if (!infile) {
		cout << "Error opening file: " << filename << endl;
		exit(EXIT_FAILURE);
	}

	int rows = read(infile), cols = read(infile); //Reads rows then cols out of the file infile
	if (!infile) {
		cout << "Error reading rows and cols from " << filename << endl;
		exit(EXIT_FAILURE);
	}
	vector<vector<int>> vec(rows, vector<int>(cols)); //2D Vector

	//YOU: Read data into vec
	for (int i = 0; i < rows; i++) {
		string line;
		getline(infile, line);
		stringstream ss(line);
		for (int j = 0; j < cols; j++) {
			int temp = 0;
			ss >> temp;
			if (!ss) break;
			vec.at(i).at(j) = temp;
		}
	}
	return vec;
}

//Prints a table of the data, this is done for you
void print_data(const vector<vector<int>> &vec) {
	int rows = vec.size();
	int cols = vec.at(0).size();
	if (rows < 1 or cols < 1) {
		cout << "Bad size.\n";
		exit(EXIT_FAILURE);
	}

	cerr << '';
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << vec.at(i).at(j) << '\t';
		}
		cout << endl;
	}
	readline("Hit a key to continue.\n");
}

//YOU: Render a picture online using the same algorithm as kerney_visualize
ColorGrid *getImage(const vector<vector<int>> &vec) {
	int rows = vec.size();
	int cols = vec.at(0).size();
	if (rows < 1 or cols < 1) {
		cout << "Bad size.\n";
		exit(EXIT_FAILURE);
	}

	//This creates the image that will be viewed in BRIDGES
	ColorGrid *cg = new ColorGrid(rows,cols); //Leave this and all the lines above alone

	//YOU: Edit the lines of code between here and the return statement to write color data to the BRIDGES web site to make it look like the kerney_visualize function that runs here in your terminal
	//This is learning through modifying

	//Super useful helpful example of how to write a single pixel to BRIDGES
	int row = 4, col = 11;
	cg->set(row,col,Color(255,0,255)); //We use -> instead of . with pointers
	//Hint 1: You should have a double nested for loop like in kerney_visualize
	//Hint 2: You should have no cout or cerr statements here - you should only write color data to the cg object using cg->set like in the example above
	//Hint 3: You can basically copy and paste most of the kerney_visualize code - just make sure you know what to change (like no couts or cerrs should be here, and instead of printing a space to the screen, call cg->set()).
	//Hint 4: Delete basically everything found in the colors.h header file, including clearscreen, setbgcolor, etc. These functions are used to print to the screen, and you will not be printing to the screen here. You will be rendering an image on BRIDGES



	return cg; //Leave this alone
}

//YOU: simulate the physics of 2D heat transfer here, units in Kelvin
//Every frame of the simulation, set the temperature of each point to be the average of the temperature that was there before and the average temperature of the 4 neighbors.
//Note: Round to the nearest int - so (2+3+2+3)/4 should be 3, not 2!
//Special rules:
//  If a temperature is -9999 it means there is a hole there, and no heat will be transferred in or out
//  If a negative temperature is given, like -90, it means the temperature is 90 but stays constant each frame
//    In other words, it will heat neighbors as if it was 90K, but it itself will not ever change temperature
void heat_transfer(vector<vector<int>> &vec) {
	int rows = vec.size();
	int cols = vec.at(0).size();
	if (rows < 1 or cols < 1) {
		cout << "Bad size.\n";
		exit(EXIT_FAILURE);
	}
	vector<vector<int>> vec2 = vec; //Hold the results of the computation in here, then swap with vec
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			cout << "H"<<endl;
		}
	}

	swap(vec2,vec); //This will switch the values in vec and vec2, making vec have the new values
}

//This is done for you
void kerney_visualize(const vector<vector<int>> &vec) {
	int rows = vec.size();
	int cols = vec.at(0).size();
	if (rows < 1 or cols < 1) {
		cout << "Bad size.\n";
		exit(EXIT_FAILURE);
	}

	//First time run, figure out the min and max values in the array
	static int max_temp = 0; //Max temperature in array at load time
	static int min_temp = INT_MAX; //Min temperature in array at load time
	if (!max_temp) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				int temp = vec.at(i).at(j);
				if (temp == -9999) //Hole
					continue;
				else if (temp < 0) {
					temp *= -1;
				}
				if (temp > max_temp) max_temp = temp;
				if (temp < min_temp) min_temp = temp;
			}
		}
		//If max equals min we'll do a division by 0 below, so fix
		if (max_temp-min_temp == 0) {
			if (min_temp == INT_MAX) {
				min_temp--;
			}
			else {
				max_temp++;
			}
		}
	}

	movecursor(0,0);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int temp = vec.at(i).at(j);
			if (temp == -9999) //Hole
				setbgcolor(0,0,0);
			else if (temp < 0) {
				temp *= -1;
			}
			if (temp >= 0) {
				//Figure out what percentage along the way this point is
				float percentage = float(temp-min_temp)/(max_temp-min_temp);
				//Clamp values to [0..1]
				if (percentage > 1) percentage = 1;
				if (percentage < 0) percentage = 0;

				//Color Scheme: LERP from blue to white from 0 to .5
				uint8_t red = 255 * (2*percentage);
				uint8_t green = 255 * (2*percentage);
				uint8_t blue = 255;
				//LERP from white to red from .5 to 1
				if (percentage >= 0.5) {
					red = 255;
					green = 255 * (2-2*percentage);
					blue = 255 * (2-2*percentage);
				}
				setbgcolor(red,green,blue);
			}
			cerr << " ";
		}
		cerr << endl;
	}
	resetcolor();
	//Put this in if you want to step through each frame instead
	readline("Hit a key\n");
//	usleep(1'000'000);
}
