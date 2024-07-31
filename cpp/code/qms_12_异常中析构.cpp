#include<iostream>
#include<string>
using namespace std;


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
	Triangle(double i, double j, double k) {
		a = i, b = j, c = k;
		cout << "triangle set " << endl;
	}

	void test() throw(BadTriangleException) {
		if (a + b <= c || b + c <= a) throw BadTriangleException(a, b, c);
		cout << "triangle set successfully" << endl;
	}

	~Triangle() {
		cout << "~Triangle()" << endl;
	}
};


int main() {
	cout << "main start" << endl;

	Triangle t0(2, 2, 3);
	t0.test();

	//当异常发生时，自动执行 try 中类的析构函数
	try {
		Triangle t1(2, 2, 3);
		Triangle t2(1, 2, 3);

		t1.test();
		t2.test();
	} 
	catch (BadTriangleException& e) {
		e.show();
	}

	cout << "main end" << endl;
	return 0;
}