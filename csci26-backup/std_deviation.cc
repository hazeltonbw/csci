#include <iostream>
#include <numeric>
#include <cmath>
#include <vector>
using namespace std;

void die() {cout << "BAD INPUT!\n"; exit(1);}
vector<double> buildVector() {
	vector<double> vec;
	cout << "Press 0 to quit.\n";
	while (1) {
		double x = 0;
		cin >> x;
		if (x == 0) break;
		if (!cin) die();
		vec.push_back(x);
	}
	return vec;
}

int main() {
	cout << "Please enter numbers to calculate the standard deviation.\n";
	vector<double> numbers = buildVector();
	if (!numbers.size()) die();
	double sum = accumulate(numbers.begin(), numbers.end(),0.0);
	double std_variance = 0;
	double mean = sum / numbers.size();
	for (auto &num : numbers)
		std_variance += pow(num - mean, 2);
	std_variance /= numbers.size();
	double std_deviation = sqrt(std_variance);

	cout << "You entered: ";
	for (auto &num : numbers) {
		cout << num << " ";
	}
	cout << "The mean is: " << mean << endl;
	cout << endl << "The standard variance is: " << std_variance << endl;
	cout << "The standard deviation is: " << std_deviation << endl;
}
