#include<iostream>
using namespace std;

template<class T>
class MaxHeap {
private:
	T* heapArray;
	int currentSize;
	int maxSize;
public:
	MaxHeap(int maxSize);
	void insert(T val);
	void pop();
	T top();
	bool empty();
	void buildHeap(T* vals, int size);
	void siftUp(int pos);
	int parent(int pos) const;
	int leftChild(int pos) const;
	int rightChild(int pos) const;
	void swap(int pos1, int pos2);
	void siftDown(int pos);
};

template<class T>
bool MaxHeap<T>::empty()
{
	return currentSize == 0;
}

template<class T>
int MaxHeap<T>::leftChild(int pos) const
{
	return 2 * pos + 1;
}

template<class T>
int MaxHeap<T>::rightChild(int pos) const
{
	return 2 * pos + 2;
}

template<class T>
int MaxHeap<T>::parent(int pos) const
{
	return (pos - 1) / 2;
}

template<class T>
void MaxHeap<T>::swap(int pos1, int pos2)
{
	T temp = heapArray[pos1];
	heapArray[pos1] = heapArray[pos2];
	heapArray[pos2] = temp;
}

template<class T>
void MaxHeap<T>::siftUp(int pos)
{
	while ((pos > 0) && (heapArray[parent(pos)] > heapArray[pos])) {
		swap(pos, parent(pos));
		pos = parent(pos);
	}
}

template<class T>
void MaxHeap<T>::siftDown(int pos)
{
	while (leftChild(pos) < currentSize) {
		int maxChild = leftChild(pos);
		if (rightChild(pos) < currentSize && heapArray[rightChild(pos)] > heapArray[leftChild(pos)]) maxChild = rightChild(pos);
		if (heapArray[maxChild] > heapArray[pos]) {
			swap(pos, maxChild);
			pos = maxChild;
		}
		else return;
	}
}

template<class T>
void MaxHeap<T>::insert(T val)
{
	if (currentSize == maxSize) return;
	heapArray[currentSize] = val;
	siftUp(currentSize);
	currentSize++;
}

template<class T>
T MaxHeap<T>::top()
{
	return heapArray[0];
}

template<class T>
void MaxHeap<T>::pop()
{
	if (currentSize == 0) return;
	swap(0, --currentSize);
	siftDown(0);
}

template<class T>
void MaxHeap<T>::buildHeap(T* vals, int size)
{
	for (int i = 0; i < size; ++i)heapArray[i] = vals[i];
	currentSize = size;
	for (int i = currentSize - 1; i >= 0; i--) siftDown(i);
}

template<class T>
MaxHeap<T>::MaxHeap(int maxSize)
{
	this->maxSize = maxSize;
	heapArray = new T[maxSize];
	currentSize = 0;
}

int main() {
	MaxHeap<int> heap(50);
	int vals[20] = { 0,1,2,3,4,5,6,7,8,9,10,34,23,43,54,213,11 };
	heap.buildHeap(vals, 17);
	while (!heap.empty()) {
		cout << heap.top() << " ";
		heap.pop();
	}
	return 0;
}
