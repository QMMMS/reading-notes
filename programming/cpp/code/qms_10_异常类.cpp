#include<iostream>
#include<string>
using namespace std;


//异常类
class BadTriangleException{
public:
	BadTriangleException(string s = "Unkonwn") :info(s) {}

	BadTriangleException(double a, double b, double c) {
		info = "Bad triangle : ";
		info.append(to_string(a));
		info.append(",");
		info.append(to_string(b));
		info.append(",");
		info.append(to_string(c));
	}
	void show() {
		cout << info << endl;
	}
private:
	string info;
};


class Triangle {
private:
	double a, b, c;
public:
	Triangle(double i, double j, double k)  throw(BadTriangleException){
		if (i + j <= k || j + k <= i) throw BadTriangleException(i, j, k);
		a = i, b = j, c = k;
		cout << "triangle set successfully" << endl;
	}
};


int main() {
	try {
		Triangle t1(2, 2, 3);
		Triangle t2(1, 2, 3);
	} //& 避免复制
	catch (BadTriangleException& e) {
		e.show();
	}

	return 0;
}