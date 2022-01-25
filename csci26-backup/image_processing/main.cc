//==================================================================================
//Write your names here, and explain what each student's code does
//Student 1 Name:
//Student 1's Filter Description:
//Student 2 Name:
//Student 2's Filter Description:
//Student 3 Name:
//Student 3's Filter Description:
//==================================================================================
//You don't need to modify this file below this line, unless you, like, want to

#include <CImg.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
using namespace cimg_library;
using namespace std;

//Student1 will write this in the file filter1.cc
void filter1(vector<vector<vector<int>>> &vec);

//Student2 will write this in the file filter2.cc
void filter2(vector<vector<vector<int>>> &vec);

//Student3 will write this in the file filter3.cc, if they exist
void filter3(vector<vector<vector<int>>> &vec);

//This code must be run with a command line parameter, so print error and quit if they don't run it right
void usage() {
	cout << "Error: this program needs to be called with a command line parameter indicating what file to open.\n";
	cout << "For example, a.out /public/kyoto.jpg\n";
	exit(1);
}

//Copy values from image into a 3D vector
const int COLORS = 3;
int cols, rows, stride;
void image_to_vec(const CImg<unsigned char> &image, vector<vector<vector<int>>> &vec) {
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			for (int k = 0; k < COLORS; k++) {
				vec.at(i).at(j).at(k) = image[k*stride+j*cols+i];
			}
		}
	}
}
//Clamp the values in vec to [0..255] then copy to image
void vec_to_image(CImg<unsigned char> &image, vector<vector<vector<int>>> &vec) {
	const int MAX_COLOR = 255;
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			for (int k = 0; k < COLORS; k++) {
				//Saturate the values, meaning values above 255 just become white, below 0 become black
				int temp = vec.at(i).at(j).at(k);
				if (temp > MAX_COLOR) temp = MAX_COLOR;
				if (temp < 0) temp = 0;
				vec[i][j][k] = temp;
				image[k*stride+j*cols+i] = temp;
			}
		}
	}
}

int main(int argc, char **argv) {
	if (argc != 2) usage(); //Check command line parameters

	//PHASE 1 - Load the image
	clock_t start_time = clock();
	CImg<unsigned char> image(argv[1]);
	
	//Set globals
	cols = image.width(); 
	rows = image.height();
	stride = cols * rows;

	//Create a new 3D vector to pass to the students' image filter code
	//Even though it is of ints, it is really uint8_t's, any value over 255 will cap at 255
	vector<vector<vector<int>>> vec(cols,vector<vector<int>>(rows,vector<int>(COLORS)));
	image_to_vec(image,vec); //Copy data from image to vec to make it easier on students
	clock_t end_time = clock();
	cerr << "Image load time: " << double (end_time - start_time) / CLOCKS_PER_SEC << " secs\n";

	//PHASE 2 - Run Student 1's Code
	start_time = clock();
	filter1(vec); 
	end_time = clock();
	cerr << "Filter 1 time: " << double (end_time - start_time) / CLOCKS_PER_SEC << " secs\n";

	//Save the file after the first filter is run
	start_time = clock();
	vec_to_image(image,vec); //Copy from the vec to the image object
	//image.save_png("filter1.png"); //Use this for higher quality output
	image.save_jpeg("filter1.jpg", 80); //Output result after filter 1 with 80% quality
	end_time = clock();
	cerr << "Time to write filter1.jpg: " << double (end_time - start_time) / CLOCKS_PER_SEC << " secs\n";

	//PHASE 3 - Run Student 2's Code
	start_time = clock();
	filter2(vec); 
	end_time = clock();
	cerr << "Filter 2 time: " << double (end_time - start_time) / CLOCKS_PER_SEC << " secs\n";
	start_time = clock();
	vec_to_image(image,vec); //Copy from the vec to the image object
	//image.save_png("filter2.png"); //Uncomment this for higher quality output
	image.save_jpeg("filter2.jpg", 80); //Output result after filter 2
	end_time = clock();
	cerr << "Time to write filter2.jpg: " << double (end_time - start_time) / CLOCKS_PER_SEC << " secs\n";

	//PHASE 4 - Run Student 3's Code, if they exist. If they exist, uncomment out this code block
	/*
	start_time = clock();
	filter3(vec); 
	end_time = clock();
	cerr << "Filter 3 time: " << double (end_time - start_time) / CLOCKS_PER_SEC << " secs\n";
	start_time = clock();
	vec_to_image(image,vec); //Copy from the vec to the image object
	//image.save_png("filter3.png"); //Uncomment this for higher quality output
	image.save_jpeg("output3.jpg", 80); //Output result after filter 3
	end_time = clock();
	cerr << "Time to write output3.jpg: " << double (end_time - start_time) / CLOCKS_PER_SEC << " secs\n";
	*/
}

