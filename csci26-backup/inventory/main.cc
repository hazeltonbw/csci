//This is how I'd do it in a data structures class, if you want to see how to do it with just CSCI40 skills, check out the other .cc file in this directory
#include <iostream>
#include <sstream>
#include <vector>
//#include <algorithm>
//#include <cctype>
//#include <cstdlib>
#include <boost/algorithm/string/trim.hpp>
#include <set>
using namespace boost;
using namespace std;

//Turn on or off all debugging couts
#define DEBUG(X)


//Upper cases a string
void uppercaseify(string &str) {for (char &ch : str) ch = toupper(ch); }
bool isCorrectFormat(const string &str) {
	// If the character is not within these two ranges of decimal values, then the character is not the correct format
	// Correct Format: [A-Z] or [0-9]
	// A = 65, Z = 90, 0 = 48, 9 = 57
	// Returns true if all characters are within the decimal ranges,
	// Returns false otherwise.
	if (str.size() < 1) return false;
	for (const char &c : str)
		if (!isupper(c) && !isdigit(c))
		   return false;
	return true;
}

void die() { cout << "Invalid Input!\n"; exit(EXIT_FAILURE); }

class Inventory {
	private:
		vector<string> cars = {};
		string name = "";
	public:

		Inventory(string new_name) { this->name = new_name; }

		bool contains(const string search) {
			for (const string &element : cars)
				if (element == search)
					return true;
			return false; //Stub
		}

		Inventory intersect(const Inventory &other) const{
			set<string> intersected;
			Inventory retval(this->name);
			const vector<string> *ptr = nullptr;

			// Put the bigger vector in a set, then sets the pointer to the smaller vector.
			if (cars.size() > other.cars.size()){
				intersected.insert(cars.begin(),cars.end());
				// Set pointer to smaller vector
				ptr = &other.cars;
			}
			else {
				intersected.insert(other.cars.begin(), other.cars.end());
				// Set pointer to smaller vector
				ptr = &cars;
			}

			// Iterate through the smaller vector, add any value that matches the bigger vector to retval Inventory
			// This will become our intersected set.
			for (const string &car : *ptr)
				if (intersected.count(car))
					retval.insert(car);
			return retval;
		}

		Inventory unionize(const Inventory &other) {
			Inventory retval(this->name);
//			vector<string> unionized;

			for (string &car : this->cars)
				retval.cars.push_back(car);
			for (string car : other.cars)
				if (!retval.contains(car))
					retval.cars.push_back(car);
			return retval;
			/*
			set<string> unionized;
			unionized.insert(cars.begin(), cars.end());
			unionized.insert(other.cars.begin(), other.cars.end());
			retval.cars.insert(retval.cars.end(), unionized.begin(), unionized.end());
			return retval;
			*/
		}

		size_t size() const{ return cars.size(); }
		void insert(const string new_car) { cars.push_back(new_car);}
		void set_name(const string name) {this->name = name;}
		string get_name() const { return name; }
//		friend istream& operator>>(istream &ins, Inventory &other);
//		friend bool operator<(Inventory &I1, Inventory &I2);
		friend ostream& operator<<(ostream &outs, const Inventory &other);
		friend bool isSubSet(Inventory* const ptrForID1, Inventory* const ptrForID2);
}; //End of inventory

class SuperSet {
	private:
		vector<Inventory> set;
	public:
		SuperSet() : set() {}
		void insert(const Inventory &new_inv) { set.push_back(new_inv); }

		//It will return the inventory matching name
		//If ignore_fail is set, then it won't die on a lack of a match
		Inventory* search(string name/*, bool ignore_fail = false*/) {
			for (Inventory &inv : set)
				if (inv.get_name() == name)
					return &inv;
			return nullptr;
		}

		//Prints all inventories in all tables
		void print_all() {
			Inventory unionized("unionized");
			for (const Inventory &inv : set) {
				unionized = unionized.unionize(inv);
				cout << inv.get_name() << ": " << inv << endl;
			}
			cout << unionized.size()  << endl;
		}

		void poset() { //Do the partial ordering of the sets here
			for (size_t i = 0;i < set.size(); i++){
				for (size_t j = 0; j < set.size(); j++){
					if (i == j) continue;
					if (isSubSet(&set.at(i), &set.at(j)) && set.at(i).size() < set.at(j).size())
						cout << set.at(i).get_name() << " " << set.at(j).get_name() << endl;
				}
			}
		}
} inventories;

//This should read from an instream, parse the input and add the vins to other
//You don't need to write this if you don't want.
/*
bool operator<(Inventory &I1, Inventory &I2) {
	return I1.size() < I2.size();
}
*/
//This should output an inventory to outs
ostream& operator<<(ostream &outs, const Inventory &other) {
	for (size_t i = 0; i < other.cars.size(); i++)
		if (i == other.cars.size() - 1)
			outs << other.cars.at(i);
		else outs << other.cars.at(i) << ", ";
	return outs;
}

bool isSubSet(Inventory* const ptrForID1, Inventory* const ptrForID2) {
	return (ptrForID1->intersect(*ptrForID2).size() == ptrForID1->size());
}

int main() {
	while (!cin.eof()) {
		//Should rewrite this using getline and strstream
		string line;
		getline(cin,line);
		stringstream ss(line);
		string first,second,third,fourth,fifth,sixth;
		ss >> first;
		trim(first);
		if (first.size() < 1) break;
		if (!cin) break;
		if (first == "CREATE") {
			ss >> second;
			trim(second);
			if (second != "TABLE") die(); // If the second word isn't TABLE, die.
			ss >> third;
			trim(third);
			if (!isCorrectFormat(third)) die(); // Check if third is in the correct format, if not die. Check isCorrectFormat function for accepted format.
			if (inventories.search(third) != nullptr) die(); // if the ID already exists, die.
			Inventory i(third);
			inventories.insert(i);

		} //END CREATE
		else if (first == "INSERT") {
			ss >> second;
			trim(second);
			if (second != "INTO") die();
			ss >> third;
			trim(third);
//			if (!isCorrectFormat(third)) die(); // Check if third is in the correct format, if not die. Check isCorrectFormat function for accepted format.
			Inventory* ptrForID1 = nullptr;
			ptrForID1 = inventories.search(third);
			if (ptrForID1 != nullptr) {
				ss >> fourth;
				trim(fourth);
				if (fourth != "VALUES") die();
				vector<Inventory *> IDS;
				Inventory *ptrForID2 = nullptr;
				while (ss) {
					getline(ss, fifth, ',');
					trim(fifth);
					if (!ss) break;
					if (fifth == third) die(); // Cant have VIN == ID
					// If a value matches an inventory name, then the user wants to copy every value in that inventory to this inventory.
//					Inventory *ptrForID2 = inventories.search(fifth);
					ptrForID2 = inventories.search(fifth);
					/*
					if (ptrForID2 != nullptr)
						IDS.push_back(ptrForID2);
					else{
						if (ptrForID1->contains(fifth)) continue;
						ptrForID1->insert(fifth);
					}
					*/
//					if (ptrForID2 != nullptr) continue;

					if (ptrForID2 != nullptr)
						*ptrForID1 = ptrForID1->unionize(*ptrForID2);
					else {
						if (ptrForID1->contains(fifth)) continue;
						ptrForID1->insert(fifth);
					}
				}
				/*
				// Deal with other tables last, per README file.
				for (Inventory * ptr : IDS)
					*ptrForID1 = ptrForID1->unionize(*ptr);
				*/
			}
			else die();
		} //END INSERT
		else if (first == "SELECT") {
			ss >> second;
			trim(second);
			if (second == "*") {
				ss >> third;
				trim(third);
				if (third != "FROM") die();
				ss >> fourth;
				trim(fourth);
				if (fourth == "*")
					inventories.print_all();
				else {
					// Fourth word should be an ID if not "*"
					if (!isCorrectFormat(fourth) && fourth != "*") die();
					Inventory *ptrForID1 = inventories.search(fourth);
					if (ptrForID1 == nullptr) die();
					ss >> fifth;
					if (fifth != "INNER") die();
					string sixth;
					ss >> sixth;
					trim(sixth);
					if (sixth != "JOIN") die();
					string seventh;
					ss >> seventh;
					trim(seventh);
					Inventory *ptrForID2 = inventories.search(seventh);
					if (ptrForID2 == nullptr) die();
					Inventory intersected = ptrForID1->intersect(*ptrForID2);
					cout << intersected << endl;
				}
			}
			else if (second == "FROM") {
				// If the second word is "FROM", the user wants to select an Inventory ID.
				ss >> third;
				trim(third);
				Inventory *ptrForID1 = inventories.search(third);
				// If there is no such ID, quit the program.
				if (ptrForID1 == nullptr) die();
				ss >> fourth;
				trim(fourth);
				if (fourth != "UNION") die();
				ss >> fifth;
				trim(fifth);
				Inventory *ptrForID2 = inventories.search(fifth);
				// If there is no such ID, quit the program.
				if (ptrForID2 == nullptr) die();
				Inventory unionized = ptrForID1->unionize(*ptrForID2);
				cout << unionized << endl;
//				cout << unionized.size() << endl;
			}
			else die();
			//YOU
		} //END SELECT
		else if (first == "IS") {
			ss >> second;
			trim(second);
			Inventory *ptrForID1 = inventories.search(second);
			if (ptrForID1 == nullptr) die();
			ss >> third;
			trim(third);
			if (third != "SUBSET") die();
			ss >> fourth;
			trim(fourth);
			Inventory *ptrForID2 = inventories.search(fourth);
			if (ptrForID2 == nullptr) die();
			cout << boolalpha << isSubSet(ptrForID1, ptrForID2) << endl;
		} //END ID
		else if (first == "POSET") {
			inventories.poset();
		} //END POSET
		else {
			DEBUG(cout << "COMMAND NOT RECOGNIZED: " << first << endl);
			die();
		}
	}
}

