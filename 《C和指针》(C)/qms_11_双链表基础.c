#include<stdlib.h>
#include<stdio.h>


typedef struct NODE {
	struct NODE* fwd;
	struct NODE* bwd;
	int value;
}Node;


/*
1st,2nd edition
int dll_insert(Node* rootp, int value) {
	Node* this;
	Node* next;
	Node* new_node;

	for (this = rootp;(next = this->fwd) != NULL;this = next) {
		if (next->value == value) return 0;
		else if (next->value > value) break;
	}

	new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) return -1;

	new_node->value = value;

	if (next != NULL) {
		new_node->fwd = next;
		if (this != rootp) { 
			new_node->bwd = this; 
			this->fwd = new_node;
		}
		else { 
			rootp->fwd = new_node;
			new_node->bwd = NULL; 
		}
		next->bwd = new_node;
	}
	else {
		new_node->fwd = NULL;
		if (this != rootp) {
			this->fwd = new_node;
			new_node->bwd = this;
		}
		else {
			rootp->fwd = new_node;
			new_node->bwd = NULL;
		}
		rootp->bwd = new_node;
	}
	return 1;
}
*/


//3rd edition
int dll_insert(register Node* rootp, int value) {
	register Node* this;
	register Node* next;
	register Node* new_node;

	for (this = rootp;(next = this->fwd) != NULL;this = next) {
		if (next->value == value) return 0;
		else if (next->value > value) break;
	}

	new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) return -1;
	new_node->value = value;

	new_node->fwd = next;
	this->fwd = new_node;

	if (this != rootp) new_node->bwd = this;
	else new_node->bwd = NULL;
	if (next != NULL) next->bwd = new_node;
	else rootp->bwd = new_node;

	return 1;
}


int main111() {

	return 0;
}