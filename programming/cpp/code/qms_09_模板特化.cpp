#include<iostream>
#include<string>
using namespace std;


template<class T>
class MyArray {
private:
	int size;
	T* element;
public:
	MyArray(int s = 0);
	~MyArray();
	T& operator[](int i)const;
};


template<class T>
MyArray<T>::MyArray(int s) :size(s){
	if (s <= 0) exit(1);
	element = new T[size];
}


template<class T>
MyArray<T>::~MyArray() {
	delete[] element;
	element = 0;
}


template<class T>
T& MyArray<T>::operator[](int i) const {
	if (i < 0 || i >= size) exit(1);
	return element[i];
}


//模板特化
template<>
class MyArray<char> {
private:
	int size;
	char* element;
public:
	MyArray(int s = 0);
	MyArray(string s);
	~MyArray();
	char& operator[](int i)const;
};


MyArray<char>::MyArray(int s) :size(s) {
	if (s <= 0) exit(1);
	element = new char[size];
}


//把 string s 放到 MyArray
MyArray<char>::MyArray(string s) :size(s.size()) {
	element = new char[size];
	for (int i = 0; i < s.size(); ++i) {
		element[i] = s[i];
	}
}


MyArray<char>::~MyArray() {
	delete[] element;
	element = 0;
}


char& MyArray<char>::operator[](int i) const {
	if (i < 0 || i >= size) exit(1);
	return element[i];
}


int main() {
	MyArray<int> intA(10);
	for (int i = 0; i < 10; ++i) intA[i] = i;
	for (int i = 0; i < 10; ++i) cout << intA[i] << " ";

	cout << endl << endl;

	MyArray<char> charA(10);
	for (int i = 0; i < 10; ++i) charA[i] = (char)('A' + i);
	for (int i = 0; i < 10; ++i) cout << charA[i] << " ";

	cout << endl << endl;

	string s = "hello";
	MyArray<char> charS(s);
	for (int i = 0; i < 5; ++i) cout << charS[i] << " ";
	return 0;
}