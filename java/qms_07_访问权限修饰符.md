# 访问权限修饰符

> 原文：https://blog.csdn.net/qq_37424916/article/details/107371305


|                  | **同一个类中** | **同一个包中** | **不同包的子类** | **不同包的无关类** |
| ---------------- | -------------- | -------------- | ---------------- | ------------------ |
| **public**       | ✔              | ✔              | ✔                | ✔                  |
| **protected**    | ✔              | ✔              | ✔                |                    |
| **无**（包访问） | ✔              | ✔              |                  |                    |
| **private**      | ✔              |                |                  |                    |

> 不同包中子类: 不同包通过继承获得关系
> 不同包中的无关类: 不同包通过直接创建对象来获得关系

## 例子1

```java
package p1;
public class Father1 {
    protected void f() {
    }    // 父类Father1中的protected方法
}

package p1;
public class Son1 extends Father1 {
}

package p2;
public class Son2 extends Father1{
}

package p1;
public class Test {
    public static void main(String[] args) {
        Son1 son1 = new Son1();
        son1.f(); // Compile OK     ----（1）
        son1.clone(); // Compile Error     ----（2）
		

        Son2 son = new Son2();    
        son2.f(); // Compile OK     ----（3）
        son2.clone(); // Compile Error     ----（4）

		Test t = new Test();
		t.clone; // Compile OK
		// 测试类test只可以使用test类的继承Object类而来的test.clone()方法
    }
}
```

看（2）（4），其中clone()方法所在类为Object类的protected方法，而Object类所在包为java.lang包。其可见性是java.lang包及其所有子类，对于语句 “son1.clone();” 和 “son2.clone(); ”，二者的clone()在类Son1、Son2中是可见的（可以使用的），但对Test类是不可见的，因此（2）（4）处编译不通过。

## 例子2

```java
package P1;
public class MyObject {
	protected Object clone() throws CloneNotSupportedException{
		return super.clone();
	}
}


package P2;
import P1.MyObject;
public class Test extends MyObject {
	public static void main(String args[]) throws CloneNotSupportedException {
		MyObject obj = new MyObject();
		obj.clone(); // Compile Error         ----（1）

		Test tobj = new Test();
		tobj.clone(); // Complie OK         ----（2）
	}
}
```

对于（1）而言，clone()方法来自于类MyObject本身，因此其可见性为包p1及MyObject的子类，虽然Test是MyObject的子类，但是由于在子类中，**只有本类实例可以访问其从基类继承而来的protected方法**，而在子类中不能访问基类实例（对象）（所调用）的protected方法。（作为子类，Test类中建立超类实例，直接去访问超类的protected方法是不可以的），因此编译不通过。

## 例子3

```java
package P1;
public class Test {
	public static void main(String args[]) throws CloneNotSupportedException {
		MyObject obj = new MyObject();
		obj.clone();   // Compile OK     ------（1）
	}
}

package P2;
public class MyObject extends Test {
}
```

对于（1）而言，由于父类中可以访问子类实例（对象）继承的父类protected修饰的方法（子父类访问权限特点：父类访问域大于子类），因此编译通过。

## 例子4

```java
package P1;
public class Test {
	public static void main(String args[]) throws CloneNotSupportedException {
		MyObject obj = new MyObject();
		obj.clone(); // Compile Error      -----（1）
	}
}

package P2;
public class MyObject extends Test {
	protected Object clone() throws CloneNotSupportedException {
		return super.clone();
	}
}
```

对于（1）而言，clone()方法来自于类MyObject是其特有方法，因此其可见性为包p2及其子类(此处没有子类)，而类Test却在包p1中，因此不满足可见性，编译不通过。

若子类与基类（父类）不在同一包中，父类中不可以使用子类实例访问（父类中没有）子类中特有的（自己的）protected修饰的成员。（毕竟没有满足同一包内和继承获得protected成员的关系）

## 例子5

```java
package P1;

public class MyObject {
	protected Object clone() throws CloneNotSupportedException{
		return super.clone();
	}
}

public class Test {
	public static void main(String[] args) throws CloneNotSupportedException {
		MyObject obj = new MyObject();
		obj.clone(); // Compile OK        ----(1)
	}
}
```

对于（1）而言，clone()方法来自于类MyObject，因此其可见性为包p1及其子类(此处没有子类)，而类Test也在包p1中，因此满足可见性，编译通过。

## 例子6

```java
package p1;

class MyObject extends Test{
}

public class Test {
    public static void main(String[] args) throws CloneNotSupportedException {
        MyObject obj = new MyObject();
        obj.clone();        // Compile OK   -------（1）
    }
}
```

对于（1）而言，clone()方法来自于类Test，因此其可见性为包p1及其子类MyObject，而类Test也在包p1中，因此满足可见性，编译通过。

## 例子7

```java
package p1;

public class Test {
}

class MyObject extends Test {
    public static void main(String[] args) {
        Test test = new Test();
        test.clone(); // Compile Error   ----- (1)
    }
}
```

对于（1）而言，首先，clone()方法所在类为Object默认根类，而Object类所在包为java.lang包。protected修饰的clone()方法其可见性是java.lang包及其所有子类，所以可以判断clone()方法所在包与子类不在同一个包中。

其次，若子类与基类不在同一包中时，子类中不能访问基类实例（对象）（所调用）的protected方法。 MyObject子类访问权限只满足本类示例的访问。


## 例子8

```java
package A;    
public class Animal {    
    protected void crowl(String c){    
        System.out.println(c);    
    }    
}


package B;
import A.Animal;
class Cat extends Animal 
{  
    
}  

public class Rat extends Animal{  
	public void crowl(){  
        this.crowl("zhi zhi"); //没有问题，继承了Animal中的protected方法——crowl(String)  
        Animal ani = new Animal();
        ani.crowl("animail jiaojiao"); //wrong, The method crowl(String) from the type Animal is not visible 
        Cat cat=new Cat();  
        cat.crowl("miao miao"); //wrong, The method crowl(String) from the type Animal is not visible  
    }  
}
```

若子类与基类不在同一包中，子类不能访问基类实例的protected方法。

若子类与基类不在同一包中，子类不能访问亲兄弟实例所继承的protected修饰的方法。

## 例子9

```java
package a;
public class A {     
	protected void m(){
		System.out.println("A m~~~");
	}
}


package b;
import a.A;
public class B extends A {
	void callM() {
		m();  // ok
		super.m(); // ok
		B b = new B(); // ok
		b.m(); // ok
	}
}


package b;
import a.A;
public class C extends A {
	void callM() {
		m(); // ok
		super.m(); // ok
		B b = new B(); // ok
		b.m();     //The method m() from type A is not visible
	}
}
```

若子类与基类不在同一包中，子类不能访问亲兄弟实例所继承的protected修饰的方法。