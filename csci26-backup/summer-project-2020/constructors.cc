#include <iostream>
using namespace std;

class Dog {
	private:
		string name;
		int age;
	public:
		Dog() {
			this->name = "N/A";
			this->age = 0;
		};
		Dog(string name, int age) {
			this->name = name;
			this->age = age;
		} 
};

int main() {
	string dog_name;
	int dog_age;
	cout << "Please enter your dog's name." << endl;
	cin >> dog_name;
	cout << "Please enter your dog's age." << endl;
	cin >> dog_age;
	if (!cin) exit(EXIT_FAILURE);
	Dog dog(dog_name, dog_age);
}
