# 异常

异常是指中断程序正常执行的一个不确定的事件。当异常发生时，程序的正常执行流程就会被打断。一般情况下，程序都会有很多条语句，如果没有异常处理机制，前面的语句一旦出现了异常，后面的语句就没办法继续执行了。有了异常处理机制后，程序在发生异常的时候就不会中断，我们可以对异常进行捕获，然后改变程序执行的流程。

关于性能问题：

1. `try-catch` 相比较没 `try-catch`，确实有一定的性能影响，但是旨在不推荐我们用 `try-catch` 来代替正常能不用 `try-catch` 的实现，而不是不让用 `try-catch`。
2. for循环内用  `try-catch` 和用 `try-catch` 包裹整个 for 循环性能差不多，但是其实两者本质上是业务处理方式的不同，跟性能扯不上关系，关键看你的业务流程处理。
3. 虽然知道`try-catch`会有性能影响，但是业务上不需要避讳其使用，业务实现优先（只要不是书中举例的那种逆天代码就行），非特殊情况下性能都是其次，有意识地避免大范围的`try-catch`，只 catch 需要的部分即可（没把握全 catch 也行，代码安全执行第一）

## 代码结构

```java
try {
    // 可能发生异常的代码
}catch {
   // 异常处理
}finally {
   // 必须执行的代码
}
```

- 如果一个 try 块后面跟了多个与之关联的 catch 块，那么应该把特定的异常（例如`ArithmeticException `）放在前面，通用型的异常（`Exception `）放在后面
- 当有多个 catch 的时候，也可以放在一起，用竖划线 `|` 隔开，例如`catch(ArithmeticException | ArrayIndexOutOfBoundsException e)`
- finally 块不是必选项，有 try 块的时候不一定要有 finally 块
- 如果 finally 块中的代码可能会发生异常，也应该使用 try-catch 进行包裹
- 即便是 try 块中执行了 return、break、continue 这些跳转语句，finally 块也会被执行
- 不执行 finally 的情况：遇到了死循环；执行了 `System.exit()` 这行代码

## 异常分类

**Exception和Error**：

- Error 的出现，意味着程序出现了严重的问题，而这些问题不应该再交给 Java 的异常处理机制来处理，程序应该直接崩溃掉，比如说 OutOfMemoryError，内存溢出了，这就意味着程序在运行时申请的内存大于系统能够提供的内存，导致出现的错误，这种错误的出现，对于程序来说是致命的。
- Exception 的出现，意味着程序出现了一些在可控范围内的问题，我们应当采取措施进行挽救。比如说之前提到的 ArithmeticException，很明显是因为除数出现了 0 的情况，我们可以选择捕获异常，然后提示用户不应该进行除 0 操作。

**checked和unchecked**：

- checked 异常（检查型异常）在源代码里必须显式地捕获或者抛出，否则编译器会提示你进行相应的操作
- unchecked 异常（非检查型异常）就是所谓的运行时异常，通常是可以通过编码进行规避的，并不需要显式地捕获或者抛出。

> checked 异常在业界是有争论的：
>
> - 它假设我们捕获了异常，并且针对这种情况作了相应的处理，但有些时候，根本就没法处理。例如ClassNotFoundException 异常
> - checked 异常也不兼容函数式编程，后面如果你写 Lambda/Stream 代码的时候，就会体验到这种苦涩
> - checked 异常并不是一无是处，强制性的 checked 异常可以让我们在编程的时候去思考，遇到这种异常的时候该怎么更优雅的去处理。特别是遇到无法用if规避的异常

**思维导图**：

![](./img/gailan-20230326090207.png)

- 只有 Throwable 类（或者子类）的对象才能使用 throw 关键字抛出，或者作为 catch 的参数类型。
- NoClassDefFoundError：程序在编译时可以找到所依赖的类，但是在运行时找不到指定的类文件，导致抛出该错误；原因可能是 jar 包缺失或者调用了初始化失败的类。
- ClassNotFoundException：当**动态加载** Class 对象的时候找不到对应的类时抛出该异常；原因可能是要加载的类不存在或者类名写错了。

## throw 和 throws

throw 关键字，用于主动地抛出异常，后面跟的是异常的对象：

```java
public class ThrowDemo {
    static void checkEligibilty(int stuage){
        if(stuage<18) {
            throw new ArithmeticException("年纪未满 18 岁，禁止观影");
        } else {
            System.out.println("请认真观影!!");
        }
    }

    public static void main(String args[]){
        checkEligibilty(10);
        System.out.println("愉快地周末..");
    }
}
```

throws 关键字出现在方法签名上，后面跟的是异常的名字：

```java
public static void main(String args[]){
    try {
        myMethod1();
    } catch (ArithmeticException e) {
        // 算术异常
    } catch (NullPointerException e) {
        // 空指针异常
    }
}
public static void myMethod1() throws ArithmeticException, NullPointerException{
    // 方法签名上声明异常
}
```

## try-with-resources

当try和finally都会抛出异常时，情况会变得复杂。看下面的代码：

```java
class MyBuffer {
    public void close() throws Exception {
        throw new Exception("close");
    }

    public void readLine() throws Exception {
        throw new Exception("readLine");
    }
}

public class TryfinallyCustomReadLineThrow {
    public static void main(String[] args) throws Exception {
        MyBuffer buff = null;
        try {
            buff = new MyBuffer();
            buff.readLine();
        } finally {
            buff.close();
        }
    }
}
```

```java
Exception in thread "main" java.lang.Exception: close
	at com.cmower.dzone.trycatchfinally.MyfinallyOutThrow.close(TryfinallyCustomOutThrow.java:17)
	at com.cmower.dzone.trycatchfinally.TryfinallyCustomOutThrow.main(TryfinallyCustomOutThrow.java:10)
```

在输出中，`readLine()` 方法的异常信息竟然被 `close()` 方法的堆栈信息吃了！这会让我们误以为要调查的目标是 `close()` 方法而不是 `readLine()` 方法

try-with-resources可以解决这个问题，finally 块消失了，取而代之的是把要释放的资源写在 try 后的 `()` 中。如果有多个资源（BufferedReader 和 PrintWriter）需要释放的话，可以直接在 `()` 中添加：

```java
try (BufferedReader br = new BufferedReader(new FileReader(decodePath));) {
    String str = null;
    while ((str =br.readLine()) != null) {
        System.out.println(str);
    }
} catch (IOException e) {
    e.printStackTrace();
}
```

如果想释放自定义资源的话，只要让它实现 AutoCloseable 接口，并提供 `close()` 方法即可

```java
public class TrywithresourcesCustom {
    public static void main(String[] args) {
        try (MyResource resource = new MyResource();) {
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

class MyResource implements AutoCloseable {
    @Override
    public void close() throws Exception {
        System.out.println("关闭自定义资源");
    }
}
```

我们看一下反编译后的字节码：

```java
try {
    MyResource resource = new MyResource();
    resource.close();
    // 主动为 try-with-resources 进行了变身
    // 在 try 中调用了 close() 方法
} catch (Exception var2) {
    var2.printStackTrace();
}
```

再添加一个 `out()` 方法：

```java
class MyResourceOut implements AutoCloseable {
    @Override
    public void close() throws Exception {
        System.out.println("关闭自定义资源");
    }

    public void out() throws Exception{
        System.out.println("沉默王二，一枚有趣的程序员");
    }
}

public class TrywithresourcesCustomOut {
    public static void main(String[] args) {
        try (MyResourceOut resource = new MyResourceOut();) {
            resource.out();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

反编译的字节码：

```java
try {
    resource.out();
} catch (Throwable var5) {  // 新增内容
    try {
        resource.close();
    } catch (Throwable var4) {
        var5.addSuppressed(var4);
    }
    throw var5;
}
resource.close();
} catch (Exception var6) {
    var6.printStackTrace();
}
```

当一个异常被抛出的时候，可能有其他异常因为该异常而被抑制住，从而无法正常抛出。这时可以通过 `addSuppressed()` 方法把这些被抑制的方法记录下来，然后被抑制的异常就会出现在抛出的异常的堆栈信息中，可以通过 `getSuppressed()` 方法来获取这些异常。这样做的好处是不会丢失任何异常，方便我们进行调试。

## 最佳实践

1. 尽量不要捕获 RuntimeException，应该用预检查的方式来规避。

   ```java
   // 正确
   if (obj != null) {
     //...
   }
   
   // 错误
   try { 
     obj.method(); 
   } catch (NullPointerException e) {
     //...
   }
   ```

2. 上面提到了，尽量使用 try-with-resource 来关闭资源。禁止在 try 块中直接关闭资源。除非资源没有实现 AutoCloseable 接口，那就在就在 finally 块关闭流

   ```java
   public void closeResourceInFinally() {
       FileInputStream inputStream = null;
       try {
           File file = new File("./tmp.txt");
           inputStream = new FileInputStream(file);
       } catch (FileNotFoundException e) {
           log.error(e);
       } finally {
           if (inputStream != null) {
               try {
                   inputStream.close();
               } catch (IOException e) {
                   log.error(e);
               }
           }
       }
   }
   ```

3. 不要捕获 Throwable，即`catch (Throwable t)`。Throwable 是 exception 和 error 的父类，如果在 catch 子句中捕获了 Throwable，很可能把超出程序处理能力之外的错误也捕获了

4. 不要省略异常信息的记录

   ```java
   public void logAnException() {
       try {
       } catch (NumberFormatException e) {
           log.error("哦，错误竟然发生了: " + e);  // 记录！！！
       }
   }
   ```

5. 不要记录（`log`）了异常又抛出了异常，容易造成错误信息的混乱。

6. 不要在 finally 块中使用 return。try 块中的 return 语句执行成功后，并不会马上返回，而是继续执行 finally 块中的语句，如果 finally 块中也存在 return 语句，那么 try 块中的 return 就将被覆盖。

7. 抛出具体定义的检查性异常而不是 Exception

   ```java
   public void foo() throws Exception { //错误方式
   }
   
   public void foo() throws SQLException  { //正确方式
   }
   ```

   它破坏了检查性（checked）异常的目的。声明的方法应该尽可能抛出具体的检查性异常。

   例如，如果一个方法可能会抛出 SQLException 异常，应该显式地声明抛出 SQLException 而不是 Exception 类型的异常。这样可以让其他开发者更好地理解代码的意图和异常处理的方式，并且可以根据 SQLException 的定义和文档来确定异常的处理方式和策略

8. 捕获具体的子类而不是捕获 Exception 类。如果只是`catch (Exception e)`，可能会捕获到一些不应该被处理的异常，从而导致程序难以识别和定位异常，也无法确定具体的异常类型和异常发生的原因

9. 自定义异常时不要丢失堆栈跟踪

   ```java
   catch (NoSuchMethodException e) {
      throw new MyServiceException("Some information: " + e.getMessage());  //错误方式
   }
   
   catch (NoSuchMethodException e) {
      throw new MyServiceException("Some information: " , e);  //正确方式
   }
   ```

10. finally 块中不要抛出任何异常，上面说过了，如果在 finally 块中抛出异常，可能会导致原始异常被掩盖

11. 不要在生产环境中使用 `printStackTrace()`，这可能会暴露敏感信息，如文件路径、用户名、密码等。将堆栈跟踪信息输出到标准错误流中，这可能会影响程序的性能和稳定性。在高并发的生产环境中，大量的异常堆栈跟踪信息可能会导致系统崩溃或出现意外的行为。此外，多线程、分布式的复杂系统中`printStackTrace()` 方法输出的堆栈跟踪信息可能并不完整或准确。在生产环境中，应该**使用日志系统来记录异常信息**，例如 log4j、slf4j、logback 等。

12. 对于不打算处理的异常，直接使用 try-finally，不用 catch

13. **早 throw 晚 catch 原则**：代码中尽可能早地抛出异常，以便在异常发生时能够及时地处理异常。同时，在 catch 块中尽可能晚地捕获异常，以便在捕获异常时能够获得更多的上下文信息，从而更好地处理异常。

14. 只抛出和方法相关的异常。相关性对于保持代码的整洁非常重要。异常最好被包裹在自定义异常

15. 切勿在代码中使用异常来进行流程控制。在代码中使用异常来进行流程控制会导致代码的可读性、可维护性和性能出现问题。

    ```java
    for (String value : values) {  // 不要这么写
        try {
            int num = Integer.parseInt(value);
            System.out.println(num);
        } catch (NumberFormatException e) {
            System.err.println(value + " is not a valid number");
        }
    }
    ```

16. 尽早验证用户输入以在请求处理的早期捕获异常

17. 一个异常只能包含在一个日志中

    ```java
    // 不要这样做
    // 在多线程环境中，这两行紧挨着的代码中间可能会输出很多其他的内容
    // 导致问题查起来会很难受。
    log.debug("Using cache sector A");
    log.debug("Using retry sector B");
    
    // 正确做法
    LOGGER.debug("Using cache sector A, using retry sector B");
    ```

18. 将所有相关信息尽可能地传递给异常

19. 终止掉被中断线程。

    ```java
    // InterruptedException 提示应该停止程序正在做的事情
    // 比如事务超时或线程池被关闭等。
    // 应该尽最大努力完成正在做的事情，并完成当前执行的线程
    // 而不是忽略 InterruptedException。
    while (true) {
      try {
        Thread.sleep(100000);
      } catch (InterruptedException e) {} //别这样做
      	doSomethingCool();
    }
    
    // 正确
    while (true) {
      try {
        Thread.sleep(100000);
      } catch (InterruptedException e) {
        break;
      }
    }
    doSomethingCool();
    ```

20. 对于重复的 try-catch，使用模板方法

    ```java
    // 这样对数据库的try-catch是很常见的，不要放得到处都是
    // 写个函数包装它
    try{
        conn.close();
    } catch(Exception ex){
        //Log Exception - Cannot close connection
    }
    ```







