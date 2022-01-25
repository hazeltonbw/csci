#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

void die(string s = "INVALID INPUT!") {
	cout << s << endl;
	exit(EXIT_FAILURE);
}

//Holds a record for a single species of Pokemon, such as Pikachu
class Pokemon {
	public:
		int index;
		string name;
		int hp, attack, defense, speed, special;
		string type1, type2;
	//YOU: Add member variable ints for each of the following:
		//index - what index it is in the pokedex
		//name (this is a string not an int)
		//hp - how much damage it takes before dying fainting
		//attack - this number gets multiplied by the move's power to determine damage
		//defense - incoming damage gets divided by this number
		//speed - whichever pokemon has the highest speed attacks first, flip a coin on a tie
		//special - like attack and defense both, but for special moves
		//Note: this is also the order the data is ordered in the file
	//YOU: Add member variables of type string for type1 and type2
		Pokemon(int index, string name, int hp, int attack, int defense, int speed, int special, string type1, string type2){
			this->index = index;
			this->name = name;
			this->hp = hp;
			this->attack = attack;
			this->defense = defense;
			this->speed = speed;
			this->special = special;
			this->type1 = type1;
			this->type2 = type2;
		}
};
vector<Pokemon> pokemon_db; //Holds all pokemon known to mankind

//This function reads from the "pokemon.txt" file in the directory and loads the data into the pokemon_db global vector
//Each row has: pokemon number, name, hp, etc.
void load_pokemon_db(string filename = "pokemon.txt", string filename2 = "types.txt") {
	ifstream ins(filename);
	if (!ins) die("Couldn't load file "s + filename);
	ifstream ins2(filename2);
	if (!ins2) die("Couldn't load file"s + filename2);
	while (ins and ins2) {
		//YOU: Read from the files the data into a temporary Pokemon, getting the stats from pokemon.txt and its types from types.txt
		//YOU: After vetting it (make sure you handle Mr. Mime properly) push it back into pokemon_db
		string temp;
		char DELIMITER = '\t';
		getline(ins, temp, DELIMITER);
		if (!ins) break;
		cout << temp << endl;
	}
}

//This class holds a record for each move in the game
class Move {
	public:
		int index;
		string name, type, category;
		int PP, power, accuracy;
		Move(int index, string name, string type, string category, int PP, int power, int accuracy) {
			this->index = index;
			this->name = name;
			this->type = type;
			this->category = category;
			this->PP = PP;
			this->power = power;
			this->accuracy = accuracy;
		}
		Move() {}
		//YOU: Add member variable for each of these:
		//int index, string name, string type, string category, int PP, int power, int accuracy
};
vector<Move> move_db;

//Reads all moves from moves.txt into move_db
//Be sure to discard all status moves
void load_move_db(string filename="moves.txt") {
	ifstream ins(filename);
	if (!ins) die("Couldn't load "s + filename);
	while (ins) {
		//YOU: Read from the file, make a temp Move with all the data read in
		//YOU: Push it back into the move_db
	}
}

//PART 2
//This conducts a one versus one battle between two pokemon of your choice
void battle_mode() {
	//Pick a Pokemon and a move for team one
	//Pick a Pokemon and a move for team two
	//Whichever Pokemon has the higher speed goes first
	//Have them do damage to each other based on their move * power * type modifier
	//Target Pokémon reduces damage based on its defense or special defense
}

//PART 2
void explore_mode() {
}

int main() {
	srand(0); //Fixed seed - don't change this
	system("figlet POKEMON");
	system("figlet ++ and \\#");
	cout << "Do you want to use the Gen1 Pokémon? (Type \"NO\" for no, anything else for yes.)\n";
	string answer;
	getline(cin,answer);
	for (char &c:answer) c = toupper(c); //Uppercaseify
	string filename1, filename2;
	if (answer == "NO") {
		cout << "Please enter the two files containing the Pokémon and types for the Pokémon.\n";
		cin >> filename1 >> filename2;
		load_pokemon_db(filename1,filename2);
	}
	else
		load_pokemon_db();

	/* Debug the load - uncomment this to see everything
	for (Pokemon p : pokemon_db) {
		cerr << "Pokedex Entry " << p.index << ": " << p.name << " hp: " << p.hp << " attack: " << p.attack;
		cerr << " defense: " << p.defense << " speed: " << p.speed << " special: " << p.special;
		cerr << " type1: " << p.type1 << " type2: " << p.type2 << endl;
	}
	*/

	string filename3;
	if (answer == "NO") {
		cout << "Please enter the file containing the moves for your Pokémon.\n";
		cin >> filename3;
		load_move_db(filename3);
	}
	else
		load_move_db();

	/*
	// DEBUG the load - uncomment this to see the results
	for (Move m : move_db) {
		if (m.index == 0) continue;
		cerr << "Move Index " << m.index << ": " << m.name << " " << " type: " << m.type << " category: " << m.category << " PP: " << m.PP << " power: " << m.power << " accuracy: " << m.accuracy << "%\n";
	}
	*/

	cout << "Do you want to\n1) Print Pokémon Data?\n2) Print Move Data?\n3) Pokemon Battle (1v1)\n4) Explore the World?\n";
	int choice = 0;
	cin >> choice;
	if (!cin || choice < 1 || choice > 4) die();
	if (choice == 1) {
		cout << "Please enter the Pokedex number of the Pokémon whose data you want to print:\n";
		int index = 0;
		cin >> index;
		if (!cin) die();
	//	Pokemon p = pokemon_db.at(index+1); //Pokedex starts at 1, this only works for Gen1 Pokémon
		for (const Pokemon &poke : pokemon_db) if (index == poke.index){
			cout << "Pokedex Entry " << poke.index << ": " << poke.name << " hp: " << poke.hp << " attack: " << poke.attack;
			cout << " defense: " << poke.defense << " speed: " << poke.speed << " special: " << poke.special;
			cout << " type1: " << poke.type1 << " type2: " << poke.type2 << endl;
		}
	}
	else if (choice == 2) {
		cout << "Please enter the move number of the move whose data you want to print:\n";
		int index = 0;
		cin >> index;
		if (!cin) die();
		Move m;
		for (const Move &mo : move_db) if (index == mo.index) m = mo;
		if (m.name == "Error") cout << "No move loaded with that index.\n";
		else
			cout << "Move Index " << m.index << ": " << m.name << " " << " type: " << m.type << " category: " << m.category << " PP: " << m.PP << " power: " << m.power << " accuracy: " << m.accuracy << "%\n";
	}
	if (choice == 3) battle_mode(); //PART 2
	else explore_mode(); //PART 2
}
