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

## 类型擦除

虚拟机没有泛型，Java 虚拟机会将泛型的类型变量擦除，并替换为限定类型（没有限定的话，就用 `Object`）

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

## 为什么无法实现真正的泛型？

由于类型擦除的存在，而且Java 的泛型不允许是基本数据类型，只能是包装器类型。我们说Java没有实现真正意义上的泛型，背后的原因是什么？

**第一，兼容性**

Java 在 2004 年已经积累了较为丰富的生态，如果把现有的类修改为泛型类，需要让所有的用户重新修改源代码并且编译，这就会导致 Java 1.4 之前打下的江山可能会完全覆灭。

> 想象一下，你的代码原来运行的好好的，就因为 JDK 的升级，导致所有的源代码都无法编译通过并且无法运行，是不是会非常痛苦？

类型擦除就完美实现了兼容性，Java 1.5 之后的类可以使用泛型，而 Java 1.4 之前没有使用泛型的类也可以保留，并且不用做任何修改就能在新版本的 Java 虚拟机上运行。

老用户不受影响，新用户可以自由地选择使用泛型，可谓一举两得。

**第二，不是“实现不了”**。Pizza，1996 年的实验语言，在 Java 的基础上扩展了泛型。

> 插一下 Java 的版本历史时间线：
>
> - 1995年5月23日，Java语言诞生
> - 1996年1月，JDK1.0 诞生
> - 1997年2月18日，JDK1.1发布
> - 1998年2月，JDK1.1被下载超过2,000,000次
> - 2000年5月8日，JDK1.3发布
> - 2000年5月29日，JDK1.4发布
> - 2004年9月30日18:00 PM，J2SE1.5 发布，即 Java 5 

也就是说，Pizza 在 JDK 1.0 的版本上就实现了“真正意义上的”泛型，泛型不仅仅可以是引用类型 String，还可以是基本数据类型。除此之外，Pizza 的泛型还可以直接使用 `new` 关键字进行声明，并且 Pizza 编译器会从构造方法的参数上推断出具体的对象类型，究竟是 String 还是 int。要知道，Java 的泛型因为类型擦除的原因，程序员是无法知道一个 ArrayList 究竟是 `ArrayList<String>` 还是 `ArrayList<Integer>` 的。

Java 的核心开发组对 Pizza 的泛型设计非常感兴趣，并且与 Pizza 的设计者 Martin 和 Phil 取得了联系，新合作了一个项目 Generic Java，争取在 Java 中添加泛型支持，但不引入 Pizza 的其他功能，比如说函数式编程。六年后它变成了 Java 5 中的泛型。但是由于兼容性引入了类型擦除而最终没有实现“真正的泛型”

虽然Generic Java的泛型扩展被搁置了六年，但 Sun 对为 GJ 编写的编译器产生了更浓厚的兴趣。事实证明，它比他们的第一个 Java 编译器更稳定、更易于维护。因此，他们决定从 2000 年发布的 1.3 版本开始，将 GJ 编译器作为标准的 javac 编译器。

## 兼容性

Java 一直以来都强调兼容性，这也是 Java 之所以能被广泛使用的主要原因之一，开发者不必担心 Java 版本升级的问题，一个在 JDK 1.4 上可以跑的代码，放在 JDK 1.5 上仍然可以跑。

针对泛型，兼容性具体表现在什么地方呢？来看下面这段代码。

```java
ArrayList<Integer> ints = new ArrayList<Integer>();
ArrayList<String> strs = new ArrayList<String>();
ArrayList list;
list = ints;
list = strs;
```

兼容性表现在上面这段代码必须得能够编译运行。怎么办呢？只能搞类型擦除了！

编译前进行泛型检测，`ArrayList<Integer>` 只能放 Integer，`ArrayList<String>` 只能放 String，取的时候就不用担心类型强转出错了。但编译后的字节码文件里，是没有泛型的，放的都是 Object。

Java 神奇就神奇在这，表面上万物皆对象，但为了性能上的考量，又存在 int、double 这种原始类型，但原始类型又没办法和 Object 兼容，于是我们就只能写 `ArrayList<Integer>` 这样很占用内存空间的代码。这恐怕也是 Java 泛型被吐槽的原因之一了。
