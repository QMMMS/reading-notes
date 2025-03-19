# Lambda 

Lambda 表达式描述了一个代码块（或者叫匿名方法），可以将其作为参数传递给构造方法或者普通方法以便后续执行。考虑下面这段代码：

```java
() -> System.out.println("沉默王二")
```

- `()` 为 Lambda 表达式的参数列表（本例中没有参数）
- `->` 标识这串代码为 Lambda 表达式（也就是说，看到 `->` 就知道这是 Lambda）
- `System.out.println("沉默王二")` 为要执行的代码，即将“沉默王二”打印到标准输出流

## 例子：Runnable

原来我们创建一个线程并启动它是这样的：

```java
public class LamadaTest {
    public static void main(String[] args) {
        new (new Runnable() {
            @Override
            public void run() {
                System.out.println("沉默王二");
            }
        }).start();
    }
}
```

通过 Lambda 表达式呢？只需要下面这样：

```java
public class LamadaTest {
    public static void main(String[] args) {
        new Thread(() -> System.out.println("沉默王二")).start();
    }
}
```

为什么可以这么写？`Runnable`在源码中，通过 `@FunctionalInterface` 标记的接口可以通过 Lambda 表达式创建实例：

```java
@FunctionalInterface
public interface Runnable
{
   public abstract void run();
}
```

## 更多实例

- 为变量赋值

  ```java
  Runnable r = () -> { System.out.println("沉默王二"); };
  r.run();
  ```

- 作为 return 结果

  ```java
  static FileFilter getFilter(String ext)
  {
      return (pathname) -> pathname.toString().endsWith(ext);
  }
  ```

- 作为数组元素

  ```java
  final PathMatcher matchers[] = {
          (path) -> path.toString().endsWith("txt"),
          (path) -> path.toString().endsWith("java")
  };
  ```

- 作为普通方法或者构造方法的参数

  ```java
  new Thread(() -> System.out.println("沉默王二")).start();
  ```

## 作用域范围

下面这段代码在编译的时候会提示错误：从lambda 表达式引用的本地变量必须是最终变量或实际上的最终变量

```java
public static void main(String[] args) {

    int limit = 10;
    Runnable r = () -> {
        limit = 5;
        for (int i = 0; i < limit; i++)
            System.out.println(i);
    };
}
```

和匿名内部类一样，不要在 Lambda 表达式主体内对方法内的局部变量进行修改，否则编译也不会通过：Lambda 表达式中要用到的，但又未在 Lambda 表达式中声明的变量，必须声明为 final 或者是 effectively final，否则就会出现编译错误

> 关于 final 和 effectively final 的区别：
>
> ```java
> final int a;
> a = 1;
> // a = 2;
> // 由于 a 是 final 的，所以不能被重新赋值
> 
> int b;
> b = 1;
> // b 此后再未更改
> // b 就是 effectively final
> 
> int c;
> c = 1;
> // c 先被赋值为 1，随后又被重新赋值为 2
> c = 2;
> // c 就不是 effectively final
> ```

那哪些情况可以修改呢？

static 变量可以在 static 方法中的 Lambda 表达式中修改：

```java
public class ModifyVariable2StaticInsideLambda {
    static int limit = 10;
    public static void main(String[] args) {
        Runnable r = () -> {
            limit = 5;
            for (int i = 0; i < limit; i++) {
                System.out.println(i);
            }
        };
        new Thread(r).start();
    }
}
```

把 limit 变量声明为 AtomicInteger：AtomicInteger 可以确保 int 值的修改是原子性的，可以使用 `set()` 方法设置一个新的 int 值，`get()` 方法获取当前的 int 值。

```java
public class ModifyVariable2AtomicInsideLambda {
    public static void main(String[] args) {
        final AtomicInteger limit = new AtomicInteger(10);
        Runnable r = () -> {
            limit.set(5);
            for (int i = 0; i < limit.get(); i++) {
                System.out.println(i);
            }
        };
        new Thread(r).start();
    }
}
```

使用数组的方式略带一些欺骗的性质，在声明数组的时候设置为 final，但更改 int 的值时却修改的是数组的一个元素：

```java
public class ModifyVariable2ArrayInsideLambda {
    public static void main(String[] args) {
        final int [] limits = {10};
        Runnable r = () -> {
            limits[0] = 5;
            for (int i = 0; i < limits[0]; i++) {
                System.out.println(i);
            }
        };
        new Thread(r).start();
    }
}
```

## Lambda 和 this 关键字

Lambda 表达式并不会引入新的作用域，这一点和匿名内部类是不同的。也就是说，Lambda 表达式主体内使用的 this 关键字和其所在的类实例相同。

```java
public class LamadaTest {
    public static void main(String[] args) {
        new LamadaTest().work();
    }

    public void work() {
        System.out.printf("this = %s%n", this);

        Runnable r = new Runnable()
        {
            @Override
            public void run()
            {
                System.out.printf("this = %s%n", this);
            }
        };
        new Thread(r).start();
        new Thread(() -> System.out.printf("this = %s%n", this)).start();
    }
}
```

```
this = LamadaTest@31befd9f
this = LamadaTest$1@1f3588c1
this = LamadaTest@31befd9f
```



