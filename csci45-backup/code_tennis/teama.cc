#include <iostream>
#include <ctime>
using namespace std;

extern "C" {
	int function_one(unsigned char *in, unsigned char *out, size_t width, size_t height);
	int function_two(int *arr, size_t n, unsigned int stride);
}

int main(int argc, char **argv) {
	int retval;
	cout << "We have " << argc << " command line parameter(s)\n";
	cout << "Parameters are:\n";
	for (int i = 0; i < argc; i++) {
		cout << "Argument " << i << ": " << argv[i] << endl;
	}

	//YOU: Create an array here
	size_t width = 5, height = 5;
	string s = "this is a secret message!";
	

	//cout << s.size() << endl;
	unsigned char *in = new unsigned char[width*height];
	unsigned char *out = new unsigned char[width*height];
	for (size_t i = 0; i < width*height; i++) {// fill *in with secret messag
		in[i] = s[i];
		out[i] = 0; // fill *out with 0's (probably not needed)
	}

	size_t n = 5;
	unsigned int stride = 5;
	int *arr = new int[n*stride];
	for (size_t i = 0; i < stride*n; i++)
		arr[i] = i+1;
	
	//OR... use a highres timer
	//Calling the assembly function like this
	clock_t start_time = clock();
	retval = function_one(in, out, width, height);
	clock_t end_time = clock();
	cout << "Running time for function_one: " << end_time - start_time << " ticks\n";
	cout << "function_one returned: " << retval << endl;

	start_time = clock();
	retval = function_two(arr, n, stride);
	end_time = clock();
	cout << "Running time for function_two: " << end_time - start_time << " ticks\n";
	cout << "function_two returned: " << retval << endl;

	for (size_t i = 0; i < width*height; i++) // fill *in with secret messag
		cout << out[i] << endl;
	for (size_t i = 0; i < stride*n; i++) // fill *in with secret messag
		cout << arr[i] << endl;
	
}
