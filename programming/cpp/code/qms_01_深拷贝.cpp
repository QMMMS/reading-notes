#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
using namespace std;


class Point {
	friend ostream& operator << (ostream& o, Point& p);

private:
	double x, y;
	char* name;
public:
	Point() = default;
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


Point::Point(const char* n, double a, double b) :x(a), y(b) {
	if (n) {
		name = new char[strlen(n) + 1];
		strcpy(name, n);
	}
	else {
		name = new char[8];
		strcpy(name, "No name");
	}
}


Point::Point(Point& p) :x(p.x), y(p.y) {
	if (p.name) {
		name = new char[strlen(p.name) + 1];
		strcpy(name, p.name);
	}
	else {
		name = new char[8];
		strcpy(name, "No name");
	}
}


Point::~Point() {
	if(name) delete[] name;
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