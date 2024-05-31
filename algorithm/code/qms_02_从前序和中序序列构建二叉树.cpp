#include<iostream>
#include<string>
#include<cmath>
using namespace std;

string in, pre;
struct Node {
	char c = 0;
	Node* left = nullptr, * right = nullptr;
};

//从中序码找到前序码中左子树的位置
int findLeftTree(int ib, int ie) {
	int pos = -1;
	for (int i = ib; i <= ie; ++i) pos = max(pos, (int)pre.find(in.at(i)));
	return pos;
}

//构建一棵子树，对应的前序码范围 [pb, pe], 中序码范围[ib, ie]
Node* buildTree(int pb, int pe, int ib, int ie) {
	if (pb > pe || ib > ie)return nullptr;
	Node* node = new Node;
	node->c = pre.at(pb);//从前序找到子树的根
	if (pb == pe || ib == ie) return node;//如果只有一个根，直接返回
	int im = in.find(pre.at(pb));//从中序找到子树的根
	if (im == ib) node->right = buildTree(pb + 1, pe, ib + 1, ie);//无左子树
	else if (im == ie)node->left = buildTree(pb + 1, pe, ib, ie - 1);//无右子树
	else {//有左子树也有右子树
		int leftTree = findLeftTree(ib, im - 1);
		node->left = buildTree(pb + 1, leftTree, ib, im - 1);
		node->right = buildTree(leftTree + 1, pe, im + 1, ie);
	}
	return node;
}

void postOrder(Node* n) {
	if (!n)return;
	postOrder(n->left);
	postOrder(n->right);
	cout << n->c;
}

int main() {
	pre = "ABDEGHCFIJ";
	in = "DBGEHACIFJ";
	Node* root = buildTree(0, pre.size() - 1, 0, in.size() - 1);
	postOrder(root);
	return 0;
}