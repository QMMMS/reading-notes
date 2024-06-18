# 反射

一般情况下，我们在使用某个类之前已经确定它到底是个什么类了，拿到手就直接可以使用 `new` 关键字来调用构造方法进行初始化，之后使用这个类的对象来进行操作。

```java
Writer writer = new Writer();
writer.setName("沉默王二");
```

像上面这个例子，就可以理解为“正射”。而反射就意味着一开始我们不知道要初始化的类到底是什么，也就没法直接使用 `new` 关键字创建对象了。

**反射**是通过一些基本信息来构造对象：

```java
Class clazz = Class.forName("com.itwanger.s39.Writer");
Method method = clazz.getMethod("setName", String.class);
Constructor constructor = clazz.getConstructor();
Object object = constructor.newInstance();
method.invoke(object,"沉默王二");
```

反射的成本要比正射的高得多。缺点主要有两个：

- **破坏封装**：由于反射允许访问私有字段和私有方法，所以可能会破坏封装而导致安全问题。
- **性能开销**：由于反射涉及到动态解析，因此无法执行 Java 虚拟机优化，再加上反射的写法的确要复杂得多，所以性能要比“正射”差很多，在一些性能敏感的程序中应该避免使用反射。

反射的主要应用场景有：

- **开发通用框架**：像 Spring，为了保持通用性，通过配置文件来加载不同的对象，调用不同的方法。
- **动态代理**：在面向切面编程中，需要拦截特定的方法，就会选择动态代理的方式，而动态代理的底层技术就是反射。
- **注解**：注解本身只是起到一个标记符的作用，它需要利用发射机制，根据标记符去执行特定的行为。

常用API功能包括：获取反射类的 Class 对象、创建反射类的对象、获取构造方法、获取字段、获取方法。

主要类位于 `java.lang.reflect` 包中，主要包括以下几个关键类：

- Class：代表一个类或接口，包含了类的结构信息（如名称、构造函数、方法、字段等）。通过 Class 对象，可以获取类的元数据并操作类的实例。
- Constructor：代表类的构造方法，用于创建类的实例。
- Method：代表类的方法，可以通过它调用类的实例方法。
- Field：代表类的字段，可以获取或修改字段的值。
- Modifier：包含方法、字段和类的访问修饰符（如 public、private 等）。

## 使用反射

```java
public class Writer {
    private int age;
    private String name;
	
    // getter, setter
}

public class ReflectionDemo1 {
    public static void main(String[] args) throws ClassNotFoundException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException {
        Writer writer = new Writer();
        writer.setName("沉默王二");
        System.out.println(writer.getName());
        
        /*****************反射********************/
        Class clazz = Class.forName("com.itwanger.s39.Writer");
        Constructor constructor = clazz.getConstructor();
        Object object = constructor.newInstance();
        Method setNameMethod = clazz.getMethod("setName", String.class);
        setNameMethod.invoke(object, "沉默王二");
        Method getNameMethod = clazz.getMethod("getName");
        System.out.println(getNameMethod.invoke(object));
    }
}
```

在 Java 中，Class 对象是一种特殊的对象，它代表了程序中的类和接口。

Java 中的每个类型（包括类、接口、数组以及基础类型）在 JVM 中都有一个唯一的 Class 对象与之对应。这个 Class 对象被创建的时机是在 JVM 加载类时，由 JVM 自动完成。

Class 对象中包含了与类相关的很多信息，如类的名称、类的父类、类实现的接口、类的构造方法、类的方法、类的字段等等。这些信息通常被称为元数据（metadata）。

除了前面提到的，通过类的全名获取 Class 对象，还有以下两种方式：

- 如果你有一个类的实例，你可以通过调用该实例的`getClass()`方法获取 Class 对象。例如：`String str = "Hello World"; Class cls = str.getClass();`
- 如果你有一个类的字面量（即类本身），你可以直接获取 Class 对象。例如：`Class cls = String.class;`

## 反射机制

要想使用反射，首先需要获得反射类的 Class 对象，每一个类，不管它最终生成了多少个对象，这些对象只会对应一个 Class 对象，这个 Class 对象是由 Java 虚拟机生成的，由它来获悉整个类的结构信息。

也就是说，`java.lang.Class` 是所有反射 API 的入口。

而方法的反射调用，最终是由 Method 对象的 `invoke()` 方法完成的，来看一下源码（JDK 8 环境下）。

```java
public Object invoke(Object obj, Object... args)
        throws IllegalAccessException, IllegalArgumentException,
        InvocationTargetException {
    // 如果方法不允许被覆盖，进行权限检查
    if (!override) {
        if (!Reflection.quickCheckMemberAccess(clazz, modifiers)) {
            Class<?> caller = Reflection.getCallerClass();
            // 检查调用者是否具有访问权限
            checkAccess(caller, clazz, obj, modifiers);
        }
    }
    // 获取方法访问器（从 volatile 变量中读取）
    MethodAccessor ma = methodAccessor;
    if (ma == null) {
        // 如果访问器为空，尝试获取方法访问器
        ma = acquireMethodAccessor();
    }
    // 使用方法访问器调用方法，并返回结果
    return ma.invoke(obj, args);
}
```

`invoke()` 方法实际上是委派给 MethodAccessor 接口来完成的。MethodAccessor 接口有三个实现类，其中的 MethodAccessorImpl 是一个抽象类，另外两个具体的实现类继承了这个抽象类。

- NativeMethodAccessorImpl：通过本地方法来实现反射调用；
- DelegatingMethodAccessorImpl：通过委派模式来实现反射调用；

`invoke()` 方法在执行的时候，会先调用 DelegatingMethodAccessorImpl，然后调用 NativeMethodAccessorImpl，最后再调用实际的方法。

之所以先采用委派实现，是为了能够在本地实现和动态实现之间切换。动态实现是另外一种反射调用机制，它是通过生成字节码的形式来实现的。如果反射调用的次数比较多，动态实现的效率就会更高，因为本地实现需要经过 Java 到 C/C++ 再到 Java 之间的切换过程，而动态实现不需要；但如果反射调用的次数比较少，反而本地实现更快一些。临界点默认是 15 次。

```java
Method setAgeMethod = clazz.getMethod("setAge", int.class);
for (int i = 0;i < 20; i++) {
    setAgeMethod.invoke(object, 18);
}
```

上面的例子中，当 i = 15 的时候，也就是第 16 次执行的时候，会改变 DelegatingMethodAccessorImpl 的委派模式 delegate 为 `(MethodAccessorImpl)(new MethodAccessorGenerator()).generateMethod()`，而之前的委派模式 delegate 为 NativeMethodAccessorImpl。

