#include<iostream>
#include<string>
using namespace std;


class Date {
	friend ostream& operator << (ostream& o, Date& s);

private:
	int year, month, day;
public:
	Date(int y, int m, int d):year(y),month(m),day(d){}
};


class Student {
	friend ostream& operator << (ostream& o, Student& s);

private:
	string name;
	Date birthday;

public:
	Student(string na,Date bir):name(na),birthday(bir){}
	Student(string na, int y, int m, int d):name(na),birthday(y,m,d){}
	//组合类构造函数
};


ostream& operator << (ostream& o, Date& s) {
	o << s.year << "." << s.month << "." << s.day;
	return o;
}


ostream& operator << (ostream& o, Student& s) {
	o << s.name << " : " << s.birthday;
	return o;
}


int main() {
	Student s1("joker", 2077, 3, 1);
	cout << s1 << endl;

	Date past(1990, 12, 29);
	Student s2("elder", past);
	cout << s2 << endl;
	return 0;
}