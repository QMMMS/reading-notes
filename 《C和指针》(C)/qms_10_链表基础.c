#include<stdlib.h>
#include<stdio.h>

#define FALSE 0
#define TURE 1


typedef struct Node {
	struct Node* link;
	int value;
}Node;


/*
//1st edition

int sll_insert(Node* current, int new_value) {
	Node* previous;
	Node* new;

	while (current != NULL && current->value < new_value) {
		previous = current;
		current = current->link;
	}

	new = (Node*)malloc(sizeof(Node));
	if (new == NULL) return FALSE;

	new->value = new_value;
	new->link = current;
	previous->link = new;

	return TURE;
}
*/


/*
2nd edition

int sll_insert(Node** rootp, int new_value) {
	Node *current,*previous,*new;

	current = *rootp;
	previous = NULL;

	while (current != NULL && current->value < new_value) {
		previous = current;
		current = current->link;
	}

	new = (Node*)malloc(sizeof(Node));
	if (new == NULL) return FALSE;
	new->value = new_value;

	new->link = current;
	if (previous == NULL) *rootp = new;
	else previous->link = new;
	

	return TURE;
}
*/


//3rd edition
int sll_insert(register Node** linkp, int new_value) {
	register Node* current;
	register Node* new;
	while ((current = *linkp) != NULL && current->value < new_value) {
		linkp = &current->link;
	}
	new = (Node*)malloc(sizeof(Node));
	if (new == NULL) return FALSE;
	new->value = new_value;

	new->link = current;
	*linkp = new;
	return TURE;

}


//注：函数与指针内容
int sll_compare_ints(void const* a, void const* b) {
	if (*(int*)a == *(int*)b) return 0;
	return 1;
}


Node* sll_search_list(Node* node, void const* value,
	int (*compare)(void const*, void const*)) {
	while (node != NULL) {
		if (compare(&node->value, value) == 0) break;
		node = node->link;
	}
	return node;
}


int main101() {

	return 0;
}