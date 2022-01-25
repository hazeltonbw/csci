#include <iostream>
#include <map>
#include <vector>
#include <cctype>
using namespace std;

//Insert a mapping from A to B, like "Socrates" => "Mortal".
void map_insert(multimap<string,string> &m,const string &a,const string &b) {
	m.insert({a,b});
}

//Return all hits for A in the map. The vector returns all hits.
//For example, searching for "Socrates" may return "Mortal" in a size-1 vector
vector<string> map_search(const multimap<string,string> &m, const string &a) {
	vector<string> retval;
	size_t count = m.count(a);
	if (count == 0) return retval;
	for (auto it = m.equal_range(a).first; it != m.equal_range(a).second; ++it)
		retval.push_back(it->second);
	return retval;
}

//We uppercaseify ALL INPUT in this program for simplicity
void upper(string &s) {
	for (char &c: s)
		c = toupper(c);
}
void die() {
	//https://www.youtube.com/watch?v=HwBmPiOmEGQ
	cout << "Dave, this conversation can serve no purpose any more. Goodbye.\n";
	exit(1);
}

vector<string> is_a(string a = "") {
	static multimap<string,string> m; //This is the IS-A database
	vector<string> retval;
	if (a == "") { //New IS-A rule
		cout << "Type a new rule, such as 'Socrates IS A man':\n";

		//Read first word in sentence - Socrates
		string hyponym; //Means "smaller concept"
		cin >> hyponym;
		if (!cin) die();
		upper(hyponym);

		//Read second word in sentence - IS
		string copula; //Copula means "is a"
		cin >> copula;
		if (!cin) die();
		upper(copula);
		if (copula != "IS") die();

		//Read third word in sentence - A
		cin >> copula;
		if (!cin) die();
		upper(copula);
		if (copula != "A") die();

		//Read forth word in sentence - man
		string hypernym; //Means "larger concept"
		cin >> hypernym;
		if (!cin) die();
		upper(hypernym);

		//Now insert it into the database, m.
		map_insert(m,hyponym,hypernym);

		//Print confirmation to the screen
		cout << "Successfully inserted rule: " << hyponym << " IS A " << hypernym << endl;
	}
	else { //IS-A query
		retval = map_search(m,a);
	}
	return retval;
}


vector<string> all_are(string a = "") {
	static multimap<string,string> m; //This is the ALL-ARE database
	vector<string> retval;
	if (a == "") { //New ALL-ARE rule
		string first, second, all, are;
		cout << "Type a new rule, such as 'ALL men ARE mortal':\n";
		cin >> all;
		upper(all);
		if (!cin or all != "ALL") die();
		cin >> first;
		upper(first);
		if (!cin) die();
		cin >> are;
		upper(are);
		if (!cin or are != "ARE") die();
		cin >> second;
		upper(second);
		if (!cin) die();
		map_insert(m, first, second);
		cout << "Successfully inserted rule: ALL " << first << " ARE " << second << endl;
	}
	else { //ALL-ARE query

		retval = map_search(m, a);
		//YOU: Do this section
	}
	return retval;
}


vector<string> some_are(string a = "") {
	static multimap<string,string> m; //This is the SOME-ARE database
	vector<string> retval;
	if (a == "") { //New SOME-ARE rule
		string first, second, some, are;
		cout << "Type a new rule, such as 'SOME dogs ARE smart':\n";
		//YOU: Do this section
		cin >> some;
		upper(some);
		if (!cin or some != "SOME") die();
		cin >> first;
		upper(first);
		if (!cin) die();
		cin >> are;
		upper(are);
		if (!cin or are != "ARE") die();
		cin >> second;
		upper(second);
		if (!cin) die();
		map_insert(m, first, second);
		cout << "Successfully inserted rule: SOME " << first << " ARE " << second << endl;
	}
	else { //SOME-ARE query
		//YOU: Do this section
		retval = map_search(m, a);
	}
	return retval;
}

vector<string> none_are(string a = "") {
	static multimap<string,string> m; //This is the NONE-ARE database
	vector<string> retval;
	if (a == "") { //New NONE-ARE rule
		string first, second, no, are;
		cin >> no;
		upper(no);
		if (!cin or no != "NO") die();
		cin >> first;
		upper(first);
		if (!cin) die();
		cin >> are;
		upper(are);
		if (!cin or are != "ARE") die();
		cin >> second;
		upper(second);
		if (!cin) die();
		map_insert(m, first, second);
		cout << "Type a new rule, such as 'NO cats ARE perfect':\n";

		//YOU: Do this section

		cout << "Successfully inserted rule: NO " << first << " ARE " << second << endl;
	}
	else { //NONE-ARE query
		//YOU: Do this section
		retval = map_search(m, a);
	}
	return retval;
}


//This function will look up people from the IS-A database and print out
// everything that we know about them.
void question() {
	cout << "What would you like to know about?\n";
	string subject;
	cin >> subject;
	if (!cin) die();
	upper(subject);
	auto isa = is_a(subject); //Look up the person in the IS-A map
	for (auto &i : isa) {
		cout << subject << " IS A " << i << endl;
	}

	//YOU:
	for (auto &i : isa) {
		auto all = all_are(i);
		for (auto &j : all) {
			cout << subject << " IS " << j << endl;
			auto second = all_are(j);
			for (auto &k : second) {
				cout << subject << " IS " << k << endl;
				auto third = all_are(k);
				for (auto &l : third) {
					cout << subject << " IS " << l << endl;
				}
			}
		}
	}

	// for all attributes for SOCRATES
	for (auto &i : isa) {
		auto some = some_are(i);
		for (auto &j : some) {
			cout << subject << " MAY BE " << j << endl;
		}
	}
	for (auto &i : isa) {
		auto some = all_are(i);
		for (auto &j : some) {
			auto second = some_are(j);
			for (auto &k : second) {
				cout << subject << " MAY BE " << k << endl;
			}
		}
	}

	// vector<string> {"socrates":"philosopher"}
	for (auto &i : isa) {
		//<vector>string {"philosopher":"awesome"}
		auto some = none_are(i);
		for (auto &j : some) {
			cout << subject << " IS NOT " << j << endl;
		}
	}

	//Now that you have all the things socrates is, go into those sets and print out everything you know about them as well.
	//If we know the following facts (from being entered earlier):
	// 1) Socrates is a men (note the plurals will look weird)
	// 2) All men are mortal
	// 3) Some mortal are smart
	// 4) No men are perfect
	//
	//And we ask to look up Socrates, it should print this:
	//SOCRATES IS A MEN
	//SOCRATES IS MORTAL
	//SOCRATES MAY BE SMART
	//SOCRATES IS NOT PERFECT

	//Don't worry about contradictory inferences, unless you want extra credit...
}

int main() {
	cout << "Hello, Dave. I am the HAL 9000.\n";
	while (true) {
		cout << "Would you like to input:\n";
		cout << "1) An IS-A rule?\n";
		cout << "2) An ALL-ARE rule?\n";
		cout << "3) A SOME-ARE rule?\n";
		cout << "4) A NONE-ARE rule?\n";
		cout << "5) Ask a question?\n";
		cout << "6) Deactivate the HAL 9000.\n";
		string s;
		cin >> s;
		if (!cin) die();
		if (s == "1") {
			is_a();
		}
		else if (s == "2") {
			all_are();
		}
		else if (s == "3") {
			some_are();
		}
		else if (s == "4") {
			none_are();
		}
		else if (s == "5") {
			question();
		}
		else if (s == "6") {
			break;
		}
		else {
			cout << "I'm sorry, Dave, but I can't do that.\n";
			continue;
		}
	}
	//For the feels: https://www.youtube.com/watch?v=c8N72t7aScY
	cout << "Daisy, Daisy, give me your answer, do...\n";
	return 0;
}
