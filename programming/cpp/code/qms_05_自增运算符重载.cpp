#include<iostream>
using namespace std;


class Increase {
	friend ostream& operator << (ostream& o, Increase& i);

private:
	int val;

public:
	Increase(int v = 0) :val(v) {}
	Increase& operator++();//重载前置运算符
	Increase operator++(int);//重载后置运算符，C++规定加一个 int 形参，但无实际作用
};


Increase& Increase::operator++() {
	val++;
	return *this;
}


Increase Increase::operator++(int) {
	Increase temp(*this);
	temp.val = this->val++;
	return temp;
}


ostream& operator << (ostream& o, Increase& i) {
	o << i.val;
	return o;
}


int main() {
	Increase i1(8);
	Increase i2 = ++ ++i1;
	cout << i1 << endl << i2 << endl;

	Increase i3 = i1++;
	cout << i1 << endl << i3 << endl;

	return 0;
}