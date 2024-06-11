# 注释

## 类注释

```java
/**
 * 计算器类
 * <strong>加粗</strong>
 * <em>斜体</em>
 * <u>下划线</u>
 * 包含方法：
 * <ul>
 * <li>加法</li>
 * <li>减法</li>
 * <li>乘法</li>
 * <li>除法</li>
 * </ul>
 */
public class Calculator{

}
```

可以使用HTML语法

> 在 Intellij IDEA 中，按下 `/**` 后敲下回车键就可以自动添加文档注释的格式，`*/` 是自动补全的。

## 方法注释

```java
/**
* 加法
* @param a 加数
* @param b 被加数
* @return sum 和
* @version 1.0
* @since 1.0
* @see calculator_test.Calculator#sub(int, int)
* @see <a href="http://qmmms.github.io">博客</a>
*/
public int add(int a, int b){
    return a + b;
}
```

see 可以建立超链接

## 字段注释

```java
/**
* 计算器的ID
*/
public static final int ID = 1;
```

## 建立文档方法

在包外输入命令：

```bash
javadoc -d <文档目录> <包名>
```

例如：

```bash
javadoc -d doc calculator_test
```

如果使用无名包：

```bash
javadoc -d doc *.java
```

> `javadoc` 命令只能为 public 和 protected 修饰的字段、方法和类生成文档。
>
> default 和 private 修饰的字段和方法的注释将会被忽略掉。因为我们本来就不希望这些字段和方法暴露给调用者。

## 注释规约

- 类、字段、方法必须使用文档注释，不能使用单行注释和多行注释。因为注释文档在 IDE 编辑窗口中可以悬浮提示，提高编码效率。

- 所有的抽象方法(包括接口中的方法)必须要用 Javadoc 注释、除了返回值、参数、 异常说明外，还必须指出该方法做什么事情，实现什么功能。

- 所有的类都必须添加创建者和创建日期。Intellij IDEA 中可以在「File and Code Templates」中设置，如：

  ```java
  /**
  * @author QMMMS
  * @date ${DATE}
  */
  ```

- 所有的枚举类型字段必须要有注释，说明每个数据项的用途。

- 代码修改的同时，注释也要进行相应的修改。



