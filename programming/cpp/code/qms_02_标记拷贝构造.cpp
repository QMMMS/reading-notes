#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
using namespace std;


class Point {
	friend ostream& operator << (ostream& o, Point& p);

private:
	double x, y;
	char* name;
	int flag;//区分构造对象和拷贝构造对象
public:
	Point(const char* n, double a, double b);
	Point(Point& p);
	~Point();
};


ostream& operator << (ostream& o, Point& p) {
	if (p.name) for (char* c = p.name; *c != '\0'; c++) o << *c;
	else o << "No name";
	o << " : ( " << p.x << " , " << p.y << " )";
	return o;
}


Point::Point(const char* n=nullptr, double a=0, double b=0) :x(a), y(b) ,flag(1){
	if (n) {
		name = new char[strlen(n) + 1];
		strcpy(name, n);
	}
	else {
		name = new char[8];
		strcpy(name, "No name");
	}
}


//在此执行浅拷贝
Point::Point(Point& p) :x(p.x), y(p.y), name(p.name), flag(0) {}


Point::~Point() {
	if (name&&flag) delete[] name;
}


int main() {
	Point p1;
	cout << p1 << endl;

	Point p2("arb", 2, 3);
	cout << p2 << endl;

	Point p3(p2);
	cout << p3 << endl;
	return 0;
}