#include <iostream>
using namespace std;

// YOU: Create a struct named 'Vector' with three integers labelled 'x', 'y', 'z'. 

struct Vector {
	int x,y,z;
};
void die() {
    cout << "BAD INPUT!" << endl;
    exit(EXIT_FAILURE);
}

// Don't worry about this, it's "MAGIC" for now. 
ostream &operator<<(ostream& outs, Vector &vec) {
    outs << "<" << vec.x << ", " <<
                             vec.y << ", " <<
                             vec.z << ">";
    return outs;
}

int main() {
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0, z1 = 0, z2 = 0;
    cout << "Please enter the x, y, and z variables for Vector 1." << endl;
    cin >> x1 >> y1 >> z1;
    if (!cin) die();
    cout << "Please enter the x, y, and z variables for Vector 2." << endl;
    cin >> x2 >> y2 >> z2;
    if (!cin) die();
    
    // YOU: Create two Vector objects labelled 'vec1', 'vec2'. 
    // Use the matching x, y, z variables in the correct object 
    // (x1,y1,z1 should be in vec1) 

	Vector vec1{x1,y1,z1};
	Vector vec2{x2,y2,z2};
    cout << "Vector 1: " << vec1 << endl;
    cout << "Vector 2: " << vec2 << endl;
  
}
