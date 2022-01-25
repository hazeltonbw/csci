#include "read.h"
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
using namespace std;

//CLASS INVARIANTS -
//1) Head and tail are null if the list is empty
//2) Head points to the top and tail to the bottom if the list has >= 1 elements
//3) size should always hold the length of the list
//4) Pointers are all hooked up correctly
class List {
	//o.O????
	//Yes, you can have a class within a class
	struct Node {
		string data; //Data Payload
		Node* next = nullptr; //Next node in the list
		Node* prev = nullptr; //Previous node in the list
		bool deleted = false; //Lazy deleted
	};

	Node *head = nullptr, *tail = nullptr;
	size_t size = 0;

  public:
	List() {}
	size_t get_size() const {
		return size;
	}
	string front() const {
		if (!head) return {};
		return head->data;
	}
	string back() const {
		if (!tail) return {};
		return tail->data;
	}
	//O(N)
	bool find(string 💎) {
		for (Node *cur = head; cur; cur = cur->next)
			if (cur->data == 💎) return true;
		return false;
	}
	//O(N) if you don't have a pointer to the place you will insert
	//O(1) if you have a pointer to the place you will insert
	void insert_after(string key, string new_data) {
		if (!find(key)) return; //O(N) extra work we shouldn't do
		//Now we know key exists, and we don't have to worry about that case
		for (Node *cur = head; cur; cur = cur->next) {
			if (cur->data == key) {
				Node *new_person = new Node{new_data, cur->next, cur};
				//Special case the tail
				if (cur == tail) tail = new_person;
				//We're in the middle of the list somewhere
				else cur->next->prev = new_person;
				cur->next = new_person;
				size++;
			}
		}
	}
	//O(N) delete
	void delete_by_name(string key) {
		//1. Is the list empty?
		//2. If the key isn't in the list
		//3. Deleting the head
		//4. Deleting the tail
		//5. Deleting from the middle
		if (!find(key)) return; //O(N) extra work we shouldn't do
		//We are now guaranteed the key is in the data structure
		for (Node *cur = head; cur; cur = cur->next) {
			if (cur->data == key) { //We have found the person we are going to delete
				if (cur->prev) cur->prev->next = cur->next;
				else head = cur->next;
				if (cur->next) cur->next->prev = cur->prev;
				else tail = cur->prev;
				delete cur;
				size--;
				break;
			}
		}
	}

	//O(1)
	void push_back(string new_string) {
		//Case 1 - push_back on an empty list
		if (!head or !tail) {
			head = tail = new Node{new_string};
		}
		//Case 2 - adding to an existing list
		else {
			Node *new_dude = new Node{new_string, nullptr, tail}; //TODO: Fix
			tail->next = new_dude;
			tail = new_dude; //tail = tail->next;
		}
		size++;
	}
	void pop_back() {
		assert(head);
		assert(tail);
		//Case 1 - Handle the case with one element in the list
		if (head == tail) {
			delete head;
			head = tail = nullptr;
		}
		//Case 2 - General case, we've got 2+ elements in the list
		else {
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
		}
		size--;
	}
	void push_front(string new_string) {
		//Case 1 - push_back on an empty list
		if (!head or !tail) {
			head = tail = new Node{new_string};
		}
		//Case 2 - adding to an existing list
		else {
			Node *new_dude = new Node{new_string, head, nullptr};
			head->prev = new_dude;
			head = new_dude;
		}
		size++;
	}
	void pop_front() {
		assert(head);
		assert(tail);
		//Case 1 - Handle the case with one element in the list
		if (head == tail) {
			delete head;
			head = tail = nullptr;
		}
		//Case 2 - General case, we've got 2+ elements in the list
		else {
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
		}
		size--;
	}
	void print_list() const {
		for (Node *cursor = head; cursor; cursor = cursor->next)
			cout << cursor->data << endl;
	}
	void reverse_print_list() const {
		for (Node *cursor = tail; cursor; cursor = cursor->prev)
			cout << cursor->data << endl;
	}

	List(const List &l) = delete; //Copy cstor = no
	List operator=(const List &l) = delete; //No assignment operator

	//Delete all remaining nodes in the LL
	~List() {
		Node *temp = head;
		while (temp != nullptr) {
			Node *copy = temp;
			temp = temp->next;
			delete copy;
			//delete copy; //double delete
			//cout << copy->data << endl; //Use after free
		}
		size = 0;
	}
};

int main() {
	List wedding_list;
	cout << endl;
	wedding_list.push_back("Lester Edralin");
	wedding_list.push_back("Wolf");
	wedding_list.push_front("Chris Johnson");
	wedding_list.delete_by_name("Lester Edralin");
	wedding_list.print_list();
	cout << endl;
	wedding_list.push_front("Aarow of the Hills");
	wedding_list.insert_after("Chris Johnson", "Emma Escandon");
	wedding_list.insert_after("Aarow of the Hills", "Nick Muia");
	wedding_list.insert_after("Aarow of the Hills", "Yoxtheimer");
	wedding_list.insert_after("Aarow of the Hills", "Bouzikian");
	wedding_list.print_list();
	cout << endl;
	cout << boolalpha << wedding_list.find("Corrente") << endl;
	wedding_list.pop_front();
	wedding_list.pop_front();
	wedding_list.pop_front();
	wedding_list.print_list();
}
