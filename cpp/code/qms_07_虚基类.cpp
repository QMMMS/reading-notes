#include<iostream>
#include<string>
using namespace std;


class Person {
protected:
	string name;
	int id;
public:
	Person(string n = "Wang", int i = 10000) :name(n), id(i) {}
};


//virtual 虚基类
class Student :virtual public Person {
protected:
	string school;
	int id;
public:
	Student(string n = "Wang", int i = 10000, string na = "University", int si = 10001) :
		Person(n, i), school(na), id(si) {}
};


class Teacher :virtual public Person {
protected:
	string titile;
	int id;

public:
	Teacher(string n = "Wang", int i = 10000, string ti = "Professor", int tid = 10001) :
		Person(n, i), titile(ti), id(tid) {}
};


class Assistant :public Student, public Teacher {
private:
	int id;
public:
	Assistant(string n = "Wang", int i = 10000, string na = "University",
		int si = 10001, string ti = "Professor", int tid = 10001, int id = 10001) :
		Person(n, i), Student(n, i, na, si), Teacher(n, i, ti, tid), id(id) {}
	//按照父类顺序依次构造

	void show() {
		cout << "name : " << name << endl;
		cout << "Person::id : " << Person::id << endl << endl;// 使用 :: 调用同名成员
		//不使用虚基类会报错，使用虚基类则只有一个 Person

		cout << "school : " << school << endl;
		cout << "Student::id : " << Student::id << endl << endl;

		cout << "titile : " << titile << endl;
		cout << "Teacher::id : " << Teacher::id << endl << endl;

		cout << "id : " << id << endl;//隐藏了父类同名成员
	}
};


int main() {
	Assistant a("Qiao", 10001, "DUT", 10002, "None", 10003, 10004);
	a.show();

	return 0;
}