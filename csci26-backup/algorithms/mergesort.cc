#include <iostream>
#include <vector>
#include <algorithm> //std::merge
using namespace std;

void mergeSort(vector<int> &vec) {
	if (vec.size() <= 1) return;
	vector<int> l(vec.begin(), vec.begin() + vec.size() / 2);
	vector<int> r(vec.begin() + vec.size() / 2, vec.end());
	mergeSort(l);
	mergeSort(r);
	merge(l.begin(), l.end(), r.begin(),r.end(),vec.begin());
}

int main() {
	vector<int> vec = {5,13,176,23,-1234,436,3250,0};
	cout << "Unsorted vector: [";
	for (size_t i = 0; i < vec.size(); i++) {
		if (i != vec.size() - 1)
			cout << vec[i] << " ,";
		else
			cout << vec[i] << "]" << endl;
	}
	mergeSort(vec);
	cout << "Sorted vector:   [";
	for (size_t i = 0; i < vec.size(); i++) {
		if (i != vec.size() - 1)
			cout << vec[i] << " ,";
		else
			cout << vec[i] << "]" << endl;
	}

}
