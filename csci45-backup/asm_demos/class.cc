//Compile with: g++ class.cc delete_bs.s 19_class.s
#include <iostream>
#include <cstring>
using namespace std;

struct SSN_Record {
	int32_t ssn; //4 bytes.
	char initials[3]; //3 bytes. Or is it?
	long long phone_number; //8 bytes?
	char *name; //4 bytes? 8 bytes?
	char *address; //4 bytes?
} bob,steve;

//C++ to assembly binding
extern "C" {
	void asm_mess_with_ssn(SSN_Record *);
	void delete_bs(char *);
}

int main() {
	string temp;
	cout << "Bob is at memory address: " << &bob << endl;
	cout << "Bob.ssn is at memory address: " << &(bob.ssn) << endl;
	cout << "Bob.initials is at memory address: " << &(bob.initials) << endl;
	cout << "Bob.phone_number is at memory address: " << &(bob.phone_number) << endl;
	cout << "Bob.name is at memory address: " << &(bob.name) << endl;
	cout << "Bob.address is at memory address: " << &(bob.address) << endl;
	cout << "Steve is at memory address: " << &steve << endl;
	cout << "Hit any key to continue" << endl;
	getline(cin,temp);

	bob.ssn = 4200;
	bob.initials[0] = 'B';
	bob.initials[1] = 'K';
	bob.initials[2] = '\0'; //Null terminator

	bob.phone_number = 1234567890123;

	//This will copy "Bob Kerney" into name
	const char *str = "Bob Kerney";
	bob.name = (char *)malloc(strlen(str)+1); //C style memory allocation
	strncpy(bob.name,str,strlen(str));

	//How to allocate 100 ints the C-style way
	//int *arr = (int *)malloc(sizeof(int) * 100); //Why not 400?
	//How to allocate 100 ints the C++ style way
	//int *arr2 = new int[100];

	//Delete the B
	delete_bs(bob.name); //Link this with delete_bs.s

	bob.address = new char[80]; //C++ style memory allocation
	strncpy(bob.address,"111 Main St.",80);
	cout << bob.name << " lives at " << bob.address << endl;
	cout << "bob.ssn: " << bob.ssn << endl;
	cout << "bob.initials: " << bob.initials << endl;
	cout << "bob.phone_number: " << bob.phone_number << endl;
	cout << "Hit any key to continue" << endl;
	getline(cin,temp);
	cout << "Calling asm_mess_with_ssn...\n";
	asm_mess_with_ssn(&bob); //Assembly will mess with it
	cout << bob.name << " lives at " << bob.address << endl;
	cout << "bob.ssn: " << bob.ssn << endl;
	cout << "bob.initials: " << bob.initials << endl;
	cout << "bob.phone_number: " << bob.phone_number << endl;

	bob.name--; //Put it back or free won't recognize it
	free(bob.name); //C style deallocation
	delete[] bob.address; //C++ style deallocation
}



