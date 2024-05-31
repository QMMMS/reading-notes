#include<iostream>
#include<stack>
using namespace std;

template<class T>
class Node {
public:
	T val;
	Node* left, * right;

	Node(T v, Node<T>* l, Node<T>* r) :val(v), left(l), right(r) {  }
};


Node<char>* buildTree() {
	Node<char>* G = new Node<char>('G', nullptr, nullptr);
	Node<char>* H = new Node<char>('H', nullptr, nullptr);
	Node<char>* I = new Node<char>('I', nullptr, nullptr);
	Node<char>* J = new Node<char>('J', nullptr, nullptr);
	Node<char>* E = new Node<char>('E', G, H);
	Node<char>* F = new Node<char>('F', I, J);
	Node<char>* D = new Node<char>('D', nullptr, nullptr);
	Node<char>* B = new Node<char>('B', D, E);
	Node<char>* C = new Node<char>('C', nullptr, F);
	Node<char>* A = new Node<char>('A', B, C);
	return A;
}

template<class T>
void visit(Node<T>* n) {
	cout << n->val;
}

template<class T>
void preOrder(Node<T>* pointer) {
	if (!pointer)return;
	visit(pointer);
	preOrder(pointer->left);
	preOrder(pointer->right);
}

template<class T>
void inOrder(Node<T>* pointer) {
	if (!pointer)return;
	inOrder(pointer->left);
	visit(pointer);
	inOrder(pointer->right);
}

template<class T>
void postOrder(Node<T>* pointer) {
	if (!pointer)return;
	postOrder(pointer->left);
	postOrder(pointer->right);
	visit(pointer);
}

template<class T>
void preOrderNoR(Node<T>* root) {
	stack < Node<T>*> s;
	s.push(root);
	while (!s.empty()) {
		Node<T>* pointer = s.top();
		s.pop();
		visit(pointer);
		if (pointer->right)s.push(pointer->right);
		if (pointer->left)s.push(pointer->left);
	}
}

template<class T>
void inOrderNoR(Node<T>* root) {
	stack < pair<Node<T>*, bool>> s;
	s.push(make_pair(root, 0));
	while (!s.empty()) {
		Node<T>* pointer = s.top().first;
		bool flag = s.top().second;
		s.pop();
		if (!flag) {
			s.push(make_pair(pointer, 1));
			if (pointer->left)s.push(make_pair(pointer->left,0));
		}
		else {
			visit(pointer);
			if(pointer->right)s.push(make_pair(pointer->right, 0));
		}
	}
}

template<class T>
void postOrderNoR(Node<T>* root) {
	stack < pair<Node<T>*, char>> s;
	s.push(make_pair(root, 'n'));
	while (!s.empty()) {
		Node<T>* pointer = s.top().first;
		char flag = s.top().second;
		s.pop();
		if (flag == 'n') {
			s.push(make_pair(pointer, 'l'));
			if (pointer->left)s.push(make_pair(pointer->left, 'n'));
		}
		else if (flag == 'l') {
			s.push(make_pair(pointer, 'r'));
			if (pointer->right)s.push(make_pair(pointer->right, 'n'));
		}
		else visit(pointer);
	}
}


template<class T>
void postOrderTwoPointer(Node<T>* root) {
	stack <Node<T>*> s;
	Node<T>* p = root, * q = root;
	while (p) {
		for (; p->left; p = p->left)s.push(p);
		while (!p->right || p->right == q) {
			visit(p);
			q = p;
			if (s.empty())return;
			p = s.top();
			s.pop();
		}
		s.push(p);
		p = p->right;
	}
}


int main() {
	Node<char>* root = buildTree();
	preOrder(root);
	cout << endl;

	preOrderNoR(root);
	cout << endl;

	inOrder(root);
	cout << endl;

	inOrderNoR(root);
	cout << endl;

	postOrder(root);
	cout << endl;

	postOrderNoR(root);
	cout << endl;

	postOrderTwoPointer(root);
	cout << endl;

	return 0;
}