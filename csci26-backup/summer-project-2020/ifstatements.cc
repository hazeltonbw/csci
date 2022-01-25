#include <iostream>
using namespace std;
void die() {cout << "BAD INPUT!\n"; exit(EXIT_FAILURE);}
int main() {
	cout << "Is the light switch in your room on? Type 1 for Yes, 0 for No." << endl;
	bool LightSwitchIsOn = 0;
	cin >> LightSwitchIsOn;
	if (!cin) die();
	
	if (LightSwitchIsOn) {
		cout << "Let there be light! \n";
	}else {
		cout << "Dark times.\n";
	}
}

