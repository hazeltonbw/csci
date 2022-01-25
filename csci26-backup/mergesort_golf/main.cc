#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
using namespace std;

//BEGIN GOLF
void mergesort(vector<unsigned int>&v,int s,int e){if(v.size()<=1)return;unsigned int m=(s+e)/2,i=0,j=0;vector<unsigned int> l(v.begin(),v.begin()+m+1),r(v.begin()+m+1,v.end()),k;mergesort(l,0,l.size()-1),mergesort(r,0,r.size()-1);while(i<l.size()&&j<r.size())k.push_back(l[i]<r[j]?l[i++]:r[j++]);if(i==l.size())while(j<r.size())k.push_back(r[j++]);else while(i<l.size())k.push_back(l[i++]);v=k;}
//END GOLF

int main() {
	vector<unsigned int> vec;
	cout << "Please insert natural numbers to sort (0 to end): ";
	while (cin) {
		unsigned int temp;
		cin >> temp;
		if (!cin) break;
		if (temp == 0) break;
		vec.push_back(temp);
	}
	if (vec.size() > 0)
		mergesort(vec,0,vec.size()-1);
	for (unsigned int i : vec) cout << i << " ";
	cout << endl;
	system("/bin/mergesort_score"); //Hope Kerney left this installed...
}
