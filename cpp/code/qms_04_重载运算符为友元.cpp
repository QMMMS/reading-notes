#include<iostream>
using namespace std;


//复数类
class Complex {
	friend ostream& operator << (ostream& o, const Complex& c);
	friend Complex operator+(int i, Complex& c);

private:
	double real, ima;
public:
	Complex(double r = 0, double i = 0) :real(r), ima(i) {}
	Complex operator+(Complex& c);
	Complex operator+(int i);
};


Complex Complex::operator+(Complex& c) {
	return Complex(this->real + c.real, this->ima + c.ima);
}


Complex Complex::operator+(int i) {
	return Complex(this->real + i, this->ima);
}


//若运算符左操作数不是本类对象，则只能将运算符重载为非成员函数
Complex operator+(int i, Complex& c) {
	return Complex(c.real + i, c.ima);
}


ostream& operator << (ostream& o, const Complex& c) {
	if (c.ima > 0)o << c.real << "+" << c.ima << "i";
	else o << c.real << c.ima << "i";
	return o;
}


int main() {
	Complex c1(2, 3);
	cout << c1 << endl;

	Complex c2(4, -7);
	cout << c2 << endl;

	cout << c1 + 1 << endl;
	cout << c2 + c1 << endl;
	cout << -9 + c2 << endl;

	return 0;
}