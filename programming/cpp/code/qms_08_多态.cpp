#include<iostream>
using namespace std;

//多态简单应用：父类指针引用子类对象，自动调用子类方法

class Shape {
public:
	virtual ~Shape();
	//虚析构函数，多态时还会调用子类析构函数

	virtual double get_area() = 0;
	//纯虚函数，需要子类再次定义
	//若有纯虚函数，则该类为抽象类，不能实例化

	virtual void show() = 0;
	//vitual 有继承性
	//vitual 只在声明时加上
};


class Square :public Shape {
private:
	double side;

public:
	Square(double s = 1) :side(s) {};
	double get_area();
	void show();
	~Square();
};


class Circle :public Shape {
private:
	double r;
public:
	Circle(double r0 = 1) :r(r0) {};
	double get_area();
	void show();
	~Circle();
};


Shape::~Shape() {
	cout << "~Shape" << endl;
}


Square::~Square() {
	cout << "~Square" << endl;
}


double Square::get_area() {
	return side * side;
}


void Square::show() {
	cout << "Square" << endl;
}


Circle::~Circle() {
	cout << "~Circle" << endl;
}


void Circle::show() {
	cout << "Circle" << endl;
}


double Circle::get_area() {
	return 3.1415926 * r * r;
}


int main() {
	Shape* members[3];

	members[0] = new Square(2);
	members[1] = new Circle(1);
	members[2] = new Square(4);

	for (Shape* p : members) {
		p->show();
	}

	cout << endl;

	for (Shape* p : members) {
		cout << p->get_area() << endl;
	}

	cout << endl;

	for (Shape* p : members) {
		delete p;
	}
	return 0;
}