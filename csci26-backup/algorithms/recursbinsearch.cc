#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int recbinarysearch(int low, int high, vector<int> &vec,int x) {
	//fix one off error for example
	int low_index = low-1;
	if (low_index < 0) low_index = 0;
	int high_index = high-1;

	if (low == high && vec[low_index] == x)
		return low;
	if (low == high && vec[low_index] != x)
		return -1;

	int mid = (low + high) / 2;
	int mid_index = mid - 1;

	if (x <= vec[mid_index]) high = mid;
	if (x > vec[mid_index]) low = mid+1;

	return recbinarysearch(low, high, vec, x);
}

bool notInVector(int number, vector<int> &vec) {
	for (auto num : vec)
		if (num == number) return false;
	return true;
}

int main() {
	vector<int> vec = {2,3,5,8};
	cout << "Vector: [";
	for (size_t i = 0; i < vec.size();i++) {
		if (i != vec.size() - 1)
			cout << vec[i] << " ,";
		else
			cout << vec[i] << "]" << endl;
	}
	cout << "Please enter a number you want to find the index for.\n";
	int input = 0;
	cin >> input;
	if (!cin or notInVector(input, vec)) {
		cout << "BAD INPUT!\n";
		exit(1);
	}
	const int LOW = 1;
	const int HIGH = vec.size();
	int index_of_desired_input = recbinarysearch(LOW, HIGH, vec, input) - 1; // -1 for 1 off error
	cout << "The index of the number you're looking for is: " << index_of_desired_input << endl;

}
