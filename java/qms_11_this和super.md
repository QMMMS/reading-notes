# this和super

## this的作用

**指向当前对象**：

```java
WithThisStudent(String name, int age) {
    this.name = name;
    this.age = age;
}
```

**调用当前类的方法**：

```java
public class InvokeCurrentClassMethod {
    void method1() {}
    void method2() {
        method1();
        
        // 在字节码文件中变成
        // this.method1();
    }

    public static void main(String[] args) {
        new InvokeCurrentClassMethod().method1();
    }
}
```

**调用当前类的构造方法**：

```java
public class InvokeConstrutor {
    InvokeConstrutor() {
        System.out.println("hello");
    }

    InvokeConstrutor(int count) {
        this();
        System.out.println(count);
    }

    public static void main(String[] args) {
        InvokeConstrutor invokeConstrutor = new InvokeConstrutor(10);
    }
}
```

> 也可以调用有参构造方法，但是`this()` 必须放在构造方法的第一行

**作为参数在方法中传递**：

```java
public class ThisAsParam {
    void method1(ThisAsParam p) {
        System.out.println(p);
    }

    void method2() {
        method1(this);
    }

    public static void main(String[] args) {
        ThisAsParam thisAsParam = new ThisAsParam();
        System.out.println(thisAsParam);
        thisAsParam.method2();  // 两次print同一个对象
    }
}
```

**作为方法的返回值**

```java
public class ThisAsMethodResult {
    ThisAsMethodResult getThisAsMethodResult() {
        return this;
    }
    
    void out() {
        System.out.println("hello");
    }

    public static void main(String[] args) {
        new ThisAsMethodResult().getThisAsMethodResult().out();
    }
}
```

`getThisAsMethodResult()` 方法返回了 this 关键字，指向的就是 `new ThisAsMethodResult()` 这个对象，所以可以紧接着调用 `out()` 方法——达到了**链式调用**的目的

## super的作用

- 指向父类对象；
- 调用父类的方法；
- `super()` 可以调用父类的构造方法。

```java
public class ReferParentField {
    public static void main(String[] args) {
        new Dog().printColor();
    }
}

class Animal {
    String color = "白色";
    
    Animal(){
        System.out.println("动物来了");
    }
    
    void eat() {
        System.out.println("动物吃...");
    }
}

class Dog extends Animal {
    String color = "黑色";

    void printColor() {
        System.out.println(color);  // 黑色
        System.out.println(super.color);  // 白色
    }
    
    @Override
    void eat() {
        System.out.println("吃...");
    }
    
    void bark() {
        System.out.println("汪汪汪...");
    }
    
    void work() {
        super.eat();  // 动物吃...
        bark();
    }
    
    Dog() {
        super();  // 调用父类的构造方法
        // 默认情况下，super() 是可以省略的，编译器会主动去调用父类的构造方法
        // super() 也可以用来调用父类的有参构造方法
        System.out.println("狗狗来了");
    }
}

```

