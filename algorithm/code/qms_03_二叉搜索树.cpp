#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree;

template <class T>
class BinarySearchTreeNode {
    friend class BinarySearchTree<T>;

private:
    T element;
    BinarySearchTreeNode<T>* leftChild;
    BinarySearchTreeNode<T>* rightChild;

public:
    BinarySearchTreeNode() {

    }
    BinarySearchTreeNode(const T& ele)
    {
        element = ele;
        leftChild = NULL;
        rightChild = NULL;
    }
    BinarySearchTreeNode(const T& ele, BinarySearchTreeNode<T>* l, BinarySearchTreeNode<T>* r)
    {
        element = ele;
        leftChild = l;
        rightChild = r;
    }
    BinarySearchTreeNode<T>* getLeftChild() const
    {
        return leftChild;
    }
    BinarySearchTreeNode<T>* getRightChild() const
    {
        return rightChild;
    }
    void setLeftChild(BinarySearchTreeNode<T>* l)
    {
        leftChild = l;
    }
    void setRightChild(BinarySearchTreeNode<T>* r)
    {
        rightChild = r;
    }
    T getValue() const
    {
        return element;
    }
    void setValue(const T& val)
    {
        element = val;
    }
    bool isLeaf() const
    {
        if (leftChild == NULL && rightChild == NULL)
            return true;
        return false;
    }
};

template <class T>
class BinarySearchTree {
private:
    BinarySearchTreeNode<T>* root;

public:
    BinarySearchTree()
    {
        root = NULL;
    }
    BinarySearchTree(BinarySearchTreeNode<T>*& r)
    {
        root = r;
    }
    void createSearchTree(); //2.3-a 构建二叉搜索树
    void visit(BinarySearchTreeNode<T>* current);
    BinarySearchTreeNode<T>* search(BinarySearchTreeNode<T>* root, T x);
    //2.3-b 二叉搜索树的查找值为x的结点，并返回此结点
    void insertNode(const T& value); //2.3-c 二叉搜索树的插入x。
    void deleteByCopying(BinarySearchTreeNode<T>*& node); //2.3-d 复制删除
    void deleteBST(BinarySearchTreeNode<T>*& root, T x);
    void inOrder(BinarySearchTreeNode<T>* root);
    void setRoot(BinarySearchTreeNode<T>* r);
    BinarySearchTreeNode<T>* getRoot();
    BinarySearchTreeNode<T>* getParent(BinarySearchTreeNode<T>* root, BinarySearchTreeNode<T>* current) const;
};

/*
函数功能：2.3-a 构建二叉搜索树
*/
template <class T>
void BinarySearchTree<T>::createSearchTree()
{
    int a;
    cout << "输入int型，以0为结束" << endl;
    cin >> a;
    while (a != 0) {
        //TODO:将变量a插入到二叉搜索树中。构建出二叉搜索树。
        insertNode(a);
        cin >> a;
    }
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::getRoot()
{
    return root;
}

template <class T>
void BinarySearchTree<T>::setRoot(BinarySearchTreeNode<T>* r)
{
    this->root = r;
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::getParent(BinarySearchTreeNode<T>* root, BinarySearchTreeNode<T>* current) const
{
    if (root != NULL) {
        if (root == current) {
            cout << "该节点为根结点，无父结点" << endl;
            return NULL;
        }
        else if (root->leftChild == current || root->rightChild == current) {
            return root;
        }
        else {
            BinarySearchTreeNode<T>* l = getParent(root->leftChild, current);
            BinarySearchTreeNode<T>* r = getParent(root->rightChild, current);
            if (l != NULL) {
                return l;
            }
            else if (r != NULL) {
                return r;
            }
            else {
                return NULL;
            }
        }
    }
    return NULL;
}

template <class T>
void BinarySearchTree<T>::visit(BinarySearchTreeNode<T>* current)
{
    cout << current->element << " ";
}

/*
TODO:2.3-b 二叉搜索树的查找值为x的结点，并返回此结点
 */
template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::search(BinarySearchTreeNode<T>* root, T x)
{
    if (!root)return NULL;
    if (root->getValue() == x)return root;
    if (x < root->getValue())return search(root->getLeftChild(), x);
    else return search(root->getRightChild(), x);
}

/*
TODO:2.3-c 二叉搜索树的插入,将value插入进去
 */
template <class T>
void BinarySearchTree<T>::insertNode(const T& value)
{
    BinarySearchTreeNode<T>* p = root, * prev = NULL;
    while (p) {
        prev = p;
        if (p->getValue() > value)p = p->getLeftChild();
        else p = p->getRightChild();
    }

    if (!root) root = new BinarySearchTreeNode<T>(value);
    else if (prev->getValue() < value)prev->setRightChild(new BinarySearchTreeNode<T>(value));
    else prev->setLeftChild(new BinarySearchTreeNode<T>(value));
}

/*
TODO:2.3-d 复制删除
*/
template <class T>
void BinarySearchTree<T>::deleteByCopying(BinarySearchTreeNode<T>*& node)
{
    BinarySearchTreeNode<T>* prev, * temp = node;
    if (node->leftChild == NULL)node = node->rightChild;
    else if (node->rightChild == NULL)node = node->leftChild;
    else {
        temp = node->leftChild;
        prev = node;
        while (temp->rightChild != NULL) {
            prev = temp;
            temp = temp->rightChild;
        }
        node->setValue(temp->getValue());
        if (prev == node) prev->setLeftChild(temp->leftChild);
        else prev->setRightChild(temp->leftChild);
    }
    delete temp;
}

template<class T>
void BinarySearchTree<T>::deleteBST(BinarySearchTreeNode<T>*& root, T x)
{
    if (!root)return;
    else {
        if (root->getValue() == x)deleteByCopying(root);
        else if (x < root->getValue()) deleteBST(root->leftChild, x);
        else deleteBST(root->rightChild, x);
    }
}

template <class T>
void BinarySearchTree<T>::inOrder(BinarySearchTreeNode<T>* root)
{
    if (root != NULL) {
        inOrder(root->leftChild);
        visit(root);
        inOrder(root->rightChild);
    }
}

int main()
{
    BinarySearchTreeNode<int>* tmp1, * tmp2;
    BinarySearchTree<int> st;
    st.createSearchTree();
    tmp1 = st.getRoot();
    st.inOrder(tmp1);
    cout << endl;
    int temp;
    cin >> temp;
    st.insertNode(temp);
    st.inOrder(tmp1);
    cout << endl;


    cout << "输入一个需要查找的值" << endl;
    cin >> temp; // 输入一个需要查找的值
    tmp2 = st.search(tmp1, temp); //找到值temp 返回结点，找不到返回NULL
    if (tmp2 != NULL) {
        cout << "查找的值为: " << tmp2->getValue() << endl;
        st.deleteBST(tmp1, temp);
        st.inOrder(tmp1);
    }
    else
        cout << "不存在值" << temp;
    return 0;
}