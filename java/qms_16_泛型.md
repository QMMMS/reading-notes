# 泛型

## 使用泛型

```java
class Arraylist<E> {
    private Object[] elementData;
    private int size = 0;

    public Arraylist(int initialCapacity) {
        this.elementData = new Object[initialCapacity];
    }
    
    public boolean add(E e) {
        elementData[size++] = e;
        return true;
    }
    
    E elementData(int index) {
        return (E) elementData[index];
    }
}
```

向 `Arraylist` 中存取数据：

```java
Arraylist<String> list = new Arraylist<String>();
list.add("沉默王三");
String str = list.get(0);
```

泛型的优秀之处：使用**类型参数**解决了元素的不确定性——参数类型为 String 的集合中是不允许存放其他类型元素的，取出数据的时候也不需要强制类型转换了。

可以在一个非泛型的类（或者泛型类）中定义泛型方法：

```java
class Arraylist<E> {
    public <T> T[] toArray(T[] a) {
        return (T[]) Arrays.copyOf(elementData, size, a.getClass());
    }
}
```

其中，`<T>`代表这是一个泛型方法。使用这个函数的代码：

```java
String [] strs = new String [4];
strs = list.toArray(strs);
```

可以使用泛型变量的限定符 `extends`，只能向其添加某个特定类以及其子类：

```java
class Arraylist<E extends Wanger> {
}
```

## 类型擦除

虚拟机没有泛型，Java 虚拟机会将泛型的类型变量擦除，并替换为限定类型（没有限定的话，就用 `Object`）

没有extend限定，`elementData`字节码如下：

```java
Object elementData(int index)
{
    return elementData[index];
}
```

有extend限定，`elementData`字节码如下：

```java
Wanger elementData(int index)
{
    return (Wanger)elementData[index];
}
```

类型擦除会导致一些问题，例如：

```java
public class Cmower {
    public static void method(Arraylist<String> list) {
        System.out.println("Arraylist<String> list");
    }

    public static void method(Arraylist<Date> list) {
        System.out.println("Arraylist<Date> list");
    }
}
```

`Arraylist<String> list` 和 `Arraylist<Date> list` 似乎是两种不同的类型，因为 String 和 Date 是不同的类。但由于类型擦除的原因，以上代码是不会通过编译的，这两个方法的参数类型在擦除后是相同的。

## 泛型通配符

通配符用于表示某种未知的类型，例如 `List<?>` 表示一个可以存储任何类型对象的 List，但是不能对其中的元素进行添加操作。通配符可以用来解决类型不确定的情况，例如在方法参数或返回值中使用。

例如，定义一个泛型方法：

```java
public static void printList(List<?> list) {
    for (Object obj : list) {
        System.out.print(obj + " ");
    }
    System.out.println();
}
```

这个方法可以接受任意类型的 List，例如 `List<Integer>`、`List<String>` 等等。

## 上限通配符

如果我们定义：

```java
class Wanger{
}
class Wangxiaoer extends Wanger{
}
```

此时下一行代码编译失败，为什么？

```java
Arraylist<Wanger> list = new Arraylist<Wangxiaoer>();
```

原因在于Java的泛型不支持协变。在这个例子中，尽管`Wangxiaoer`是`Wanger`的子类，`Arraylist<Wanger>`和`Arraylist<Wangxiaoer>`被视为完全不同的类型，没有父子关系。

利用 `<? extends Wanger>` 形式的通配符，通配符只能接受 Wanger 或 Wanger 的子类。

```java
Arraylist<? extends Wanger> list2 = new Arraylist<>(4);
// list2.add(new Wanger());
```

注意！list2 并不允许通过 `add(E e)` 方法向其添加 `Wanger` 或者 `Wangxiaoer` 的对象，唯一例外的是 `null`。因为编译器在编译时无法确定`list2`具体持有的元素类型，因此它阻止你调用任何带有泛型参数`E`的方法（如`add(E e)`），因为编译器无法保证方法参数的类型安全。

虽然不能通过 `add(E e)` 方法往 list2 中添加元素，但可以给它赋值。

```java
Arraylist<Wanger> list = new Arraylist<>(4);
list.add(new Wanger());
list.add(new Wangxiaoer());
Arraylist<? extends Wanger> list2 = list;
// 之后可以读取数据，但牺牲了写入的能力
```

或者在函数中使用：

```java
public static void printNumberList(List<? extends Number> list) {
    for (Number num : list) {
        System.out.print(num + " ");
    }
    System.out.println();
}
```

