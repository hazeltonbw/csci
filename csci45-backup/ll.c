#include <stdlib.h>
#include <stdio.h>

//C only has call by value and call by pointer

typedef struct _Node {
	int data;
	struct _Node *next, *prev;
} Node;

void node_init(Node *node) {
	node->next = node->prev = 0;
	node->data = 0;
}
void node_init2(Node *node, int data) {
	node->next = node->prev = 0;
	node->data = data;
}

typedef struct _List {
	Node *head, *tail;
	int size;
} List;

void list_init(List *list) {
	list->head = list->tail = 0;
	list->size = 0;
}

void list_push_back(List *list, int data) {
	if (!list) return;
	if (!list->head || !list->tail) { // Empty list
		list->head = list->tail = (Node *) malloc(sizeof(Node));
		node_init2(list->head, data);//Cstor
		return;
	}	
	else {
		Node *new_dude = (Node *) malloc(sizeof(Node));
		node_init2(new_dude, data);
		list->tail->next = new_dude;
		list->size++;
		new_dude->prev= list->tail;
		list->tail = new_dude;
	}
}

void print_list(List *list) {
	for (Node *temp = list->head; temp; temp = temp->next)
		printf("%i\n", temp->data);
}

int main() {
	List list;
	list_init(&list);
	int count = 0;
	while (1) {
		int temp = 0;
		printf("Please enter an integer to add to the list, you have entered %i so far.\n", count++);
		scanf("%i", &temp);
		if (temp == 0) break;
		list_push_back(&list, temp);
	}
	printf("\n");
	print_list(&list);
}
