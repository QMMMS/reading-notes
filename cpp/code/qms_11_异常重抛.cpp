#include<iostream>
using namespace std;


class Cylinder {
private:
	double radius;
	double height;
public:
	Cylinder(double r = 1, double he = 1) :radius(r), height(he) {}

	double area() throw(double);
	double volume() throw(double);
};


double Cylinder::area() throw(double) {
	try {
		if (radius <= 0) throw radius;
		return 3.1415926 * radius * radius;
	}
	catch (double radius) {
		cout << "area() throw a exception, radius = " << radius << endl;
		throw;//重抛
	}
}


double Cylinder::volume() throw(double) {
	try {
		return area() * height;
	}
	catch (double radius) {
		cout << "volume() throw a exception, radius = " << radius << endl;
		throw;//重抛
	}
}


int main() {
	Cylinder c1(-4);
	try {
		cout << c1.volume() << endl;
	}
	catch (double radius) {
		cout << "main() throw a exception, radius = " << radius << endl;
	}
	
	return 0;
}