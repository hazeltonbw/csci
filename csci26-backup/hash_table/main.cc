#include <iostream>
#include "hash.h"
using namespace std;

/*
 * Hash Table 
 * Hash Table
 * Super Cool
 *
 * Hash Table
 * Hash Table
 * Let's have Fun!
 */

//For this assignment, you will implement a hash table.
//You must implement four different commands:
// INSERT - adds a number to the hash table
// SEARCH - tests to see if a number is in the hash table
// REMOVE - removes a number from the hash table
// CHANGE - if a number is in the hash table, removes it and replaces it with another number

/* Sample input 
INSERT 7
SEARCH 7
INSERT 9
INSERT 9
REMOVE 9
SEARCH 9
CHANGE 9 1
CHANGE 7 9
SEARCH 9
*/

/* Sample output
7 IN TABLE
9 NOT IN TABLE
9 IN TABLE
*/

int main(int argc, char **argv) {
	int mode = LINEAR;
	if (argc > 1) mode = atoi(argv[1]);
	if (mode < LINEAR or mode > DOUBLE) mode = LINEAR;
	cerr << "Mode == " << mode << endl;

	Hash<int,10000> table(mode); //For the input tester, make it size 11

	//Delete this sample code...
	table.insert(10);
	table.search(10);
	table.change(10,20);
	table.remove(20);
}

