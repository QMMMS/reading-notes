# Object

在 Java 中，经常提到一个词“万物皆对象，除了基本数据类型”，其中的“万物”指的是 Java 中的所有类，而这些类都是 Object 类的子类。

Object 主要提供了 11 个方法，大致可以分为六类：

![](./img/objex.png)

按照约定，相等的对象必须具有相等的哈希码。如果重写了 equals 方法，就应该重写 **hashCode** 方法。可以使用 Objects.hash() 方法来生成哈希码。

```java
public int hashCode() {
    return Objects.hash(name, age);
}
```

**equals** 方法用于比较 2 个对象的内存地址是否相等。如果比较的是两个对象的值是否相等，就要重写该方法。

```java
public boolean equals(Object obj) {
    if (this == obj) {
        return true;
    }
    if (obj instanceof Person1) {
        Person1 p = (Person1) obj;
        return this.name.equals(p.getName()) && this.age == p.getAge();
    }
    return false;
}
```

**对象拷贝**：返回此对象的一个副本。默认实现只做浅拷贝，且类必须实现 Cloneable 接口。

```java
protected native Object clone() throws CloneNotSupportedException
```

Object 本身没有实现 Cloneable 接口，所以在不重写 clone 方法的情况下直接调用该方法会发生 CloneNotSupportedException 异常。

**对象转字符串**：返回对象的字符串表示。默认实现返回类名@哈希码的十六进制表示，但通常会被重写以返回更有意义的信息。

```java
public String toString() {
    return getClass().getName() + "@" + Integer.toHexString(hashCode());
}
```

```java
public String toString() {
    return "Person{" +
            "name='" + name + '\'' +
            ", age=" + age +
            '}';
}
```

> 这项工作也可以直接交给 IDE，比如 IntelliJ IDEA，直接右键选择 Generate，然后选择 toString 方法，就会自动生成一个 toString 方法。

**多线程调度**：每个对象都可以调用 Object 的 wait/notify 方法来实现等待/通知机制。

```java
public class WaitNotifyDemo {
    public static void main(String[] args) {
        Object lock = new Object();
        new Thread(() -> {
            synchronized (lock) {
                System.out.println("线程1：我要等待");
                try {
                    lock.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println("线程1：我被唤醒了");
            }
        }).start();
        new Thread(() -> {
            synchronized (lock) {
                System.out.println("线程2：我要唤醒");
                lock.notify();
                System.out.println("线程2：我已经唤醒了");
            }
        }).start();
    }
}
```

- 线程 1 先执行，它调用了 `lock.wait()` 方法，然后进入了等待状态。
- 线程 2 后执行，它调用了 `lock.notify()` 方法，然后线程 1 被唤醒了。

**反射**：用于获取对象的类信息，如类名。

```java
Person p = new Person();
Class<? extends Person> aClass = p.getClass();
System.out.println(aClass.getName());
```

**垃圾回收**：当垃圾回收器决定回收对象占用的内存时调用此方法。用于清理资源，但 Java 不推荐使用，因为它不可预测且容易导致问题，Java 9 开始已被弃用。