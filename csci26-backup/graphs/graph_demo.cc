#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <limits>
#include <queue>
#include <algorithm>
using namespace std;

struct Contact {
	size_t index;
	double duration;
};

struct Person {
	string name;
	list<Contact> contacts;
	bool infected;
};

int main() {
	system("figlet C++ovid Death Stranding | cowsay -n -f vader.cow | lolcat");
	//Adjacency List version
	vector<Person> graph;
	//Add all the vertices to the graph
	while(true) {
		string name;
		cout << "Please enter the name of a person to add to the graph. (DONE to be done)\n";
		cin >> name;
		if (name == "DONE") break;
		bool okay = true;
		for (const auto &person : graph) if (person.name == name) okay = false;
		if (okay)
			graph.push_back({name,{},false});
		else
			cout << "Sorry that is a duplicate name, you can't have dopplegangers up in here.\n";
	}
	//Add all the edges to the graph
	while(true) {
		string from, to;
		cout << "Please enter the name of a person who had contact with another person\n";
		cin >> from;
		cout << "Please enter the name of the other person\n";
		cin >> to;
		double duration = 0;
		cout << "How long were they in contact for? (0 to be done)\n";
		cin >> duration;
		if (duration == 0) break;
		if (duration < 0) {
			cout << "Bad duration.\n";
			continue;
		}
		size_t index1 = numeric_limits<size_t>::max(), index2 = numeric_limits<size_t>::max();
		for (size_t i = 0; i < graph.size(); i++) {
			if (graph[i].name == from) index1 = i;
			if (graph[i].name == to)   index2 = i;
		}
		if (index1 == numeric_limits<size_t>::max()) {
			cout << from << " not found in graph.\n";
			continue;
		}
		if (index2 == numeric_limits<size_t>::max()) {
			cout << to << " not found in graph.\n";
			continue;
		}
		//Undirected graph (bidirectional graph)
		graph[index1].contacts.push_back({index2,duration});
		graph[index2].contacts.push_back({index1,duration});
	}
	//Randomly infect someone
	srand(time(0));
	size_t index = rand() % graph.size();
	graph.at(index).infected = true;
	cout << "WARNING: " << graph[index].name << " is patient zero!\n";
	//Graph traversal
	deque<size_t> to_process = {index}; //A list of people to infect
	deque<size_t> processed; //People we have finished infecting
	while (to_process.size()) { //While there are still people to be infected
		const Person &temp = graph.at(to_process.front());
		cout << "Processing: " << temp.name << endl;
		for (const Contact &contact : temp.contacts) {
			size_t index = contact.index;
			//If they are on the to_process list already, skip
			if (find(to_process.begin(),to_process.end(),index) != to_process.end()) continue;
			//If they are on the processed list already, skip
			if (find(processed.begin(),processed.end(),index) != processed.end()) continue;
			cout << "Infecting: " << graph.at(index).name << endl;
			graph.at(index).infected = true; //Infect them with the rona
			to_process.push_back(index); //Add them to the to_process list
		}
		processed.push_back(to_process.front()); //Add the current vertex to the processed list
		to_process.pop_front();
	}
	//Print out who is infected
	for (const Person &p : graph)
		cout << p.name << " is " << (p.infected ? "infected" : "not infected") << endl;
}








