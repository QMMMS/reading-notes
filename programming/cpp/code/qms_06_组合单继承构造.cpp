#include<iostream>
#include<string>
using namespace std;


class Person {
	friend ostream& operator<<(ostream& o, Person& p);

protected:
	string name;
	int age;
public:
	Person(string n = "Wang", int a = 18) :name(n), age(a) {}
};


class School {
	friend ostream& operator<<(ostream& o, School& s);

private:
	string name;
	string city;
public:
	School(string na = "University", string ci = "Beijing") :name(na), city(ci) {}
};


ostream& operator<<(ostream& o, Person& p) {
	o << p.name << "," << p.age;
	return o;
}


ostream& operator<<(ostream& o, School& s) {
	o << s.name << "," << s.city;
	return o;
}


class Student :public Person {
	friend ostream& operator<<(ostream& o, Student& s);

private:
	int id;
	School school;
public:
	Student(string n = "Wang", int a = 18, string na = "University", string ci = "Beijing", int i = 10001) :
		Person(n, a), school(na, ci), id(i) {}
	//先父类，再内嵌对象，再自己
};


ostream& operator<<(ostream& o, Student& s) {
	o << s.name << "," << s.age << " in " << s.school;
	return o;
}


int main() {
	Student me("QMMMS", 19, "DUT", "DaLian");
	cout << me << endl;
	return 0;
}