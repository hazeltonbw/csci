#include <vector>
#include <iostream>
using namespace std;

struct Foo {
    char c;
    int x;
    float f;

};

int main() {
    Foo f;
    cout << (int)&f << endl;
    cout << (int)&f.c << endl;
    cout << (int)&f.x << endl;
}
