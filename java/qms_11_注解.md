# 注解

注解（Annotation）是在 Java 1.5 时引入的概念，同 class 和 interface 一样，也属于一种类型。注解提供了一系列数据用来装饰程序代码（类、方法、字段等），但是注解并不是所装饰代码的一部分，它**对代码的运行效果没有直接影响**，由编译器决定该执行哪些操作。

注解的**生命周期**：

- SOURCE：在源文件中有效，被编译器丢弃。
- CLASS：在编译器生成的字节码文件中有效，但在运行时会被处理类文件的 JVM 丢弃。
- RUNTIME：在运行时有效。这也是注解生命周期中最常用的一种策略，它允许程序通过反射的方式访问注解，并根据注解的定义执行相应的代码。

注解的**目标**定义了注解将适用于哪一种级别的 Java 代码上：

- TYPE：用于类、接口、注解、枚举
- FIELD：用于字段（类的成员变量），或者枚举常量
- METHOD：用于方法
- PARAMETER：用于普通方法或者构造方法的参数
- CONSTRUCTOR：用于构造方法
- LOCAL_VARIABLE：用于变量
- ANNOTATION_TYPE：用于注解
- PACKAGE：用于包
- TYPE_PARAMETER：用于泛型参数
- TYPE_USE：用于声明语句、泛型或者强制转换语句中的类型
- MODULE：用于模块

## 创建注解

```java
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.FIELD)
public @interface JsonField {
    public String value() default "";
}
```

- JsonField 注解的生命周期是 RUNTIME，也就是运行时有效。
- JsonField 注解装饰的目标是 FIELD，也就是针对字段的。
- 创建注解需要用到 `@interface` 关键字。
- JsonField 注解有一个参数，名字为 value，类型为 String，默认值为一个空字符串。

value 允许注解的使用者提供一个无需指定名字的参数。举个例子，我们可以在一个字段上使用 `@JsonField(value = "沉默王二")`，也可以把 `value =` 省略，变成 `@JsonField("沉默王二")`。

关于`default ""`，它允许我们在一个字段上直接使用 `@JsonField`，而无需指定参数的名和值。

## 使用注解

```java
public class Writer {
    private int age;

    @JsonField("writerName")
    private String name;

    @JsonField
    private String bookName;

    public Writer(int age, String name, String bookName) {
        this.age = age;
        this.name = name;
        this.bookName = bookName;
    }

    // getter / setter

    @Override
    public String toString() {
        return "Writer{" +
                "age=" + age +
                ", name='" + name + '\'' +
                ", bookName='" + bookName + '\'' +
                '}';
    }
}
```

序列化类 JsonSerializer，内容如下：

```java
public class JsonSerializer {
    public static String serialize(Object object) throws IllegalAccessException {
        Class<?> objectClass = object.getClass();
        Map<String, String> jsonElements = new HashMap<>();
        
        // 通过反射的方式获取对象声明的所有字段
        for (Field field : objectClass.getDeclaredFields()) {
            field.setAccessible(true); 
            // 将反射对象的可访问性设置为 true，供序列化使用
            // 如果没有这个步骤的话，private 字段是无法获取的
            
            if (field.isAnnotationPresent(JsonField.class)) {
                // 判断字段是否装饰了 `JsonField` 注解
                jsonElements.put(getSerializedKey(field), (String) field.get(object));
            }
        }
        
        // 借助 Stream 流的方式返回格式化后的 JSON 字符串
        return toJsonString(jsonElements);
    }

    private static String getSerializedKey(Field field) {
        // 获取字段上注解的值，如果注解的值是空的，则返回字段名
        String annotationValue = field.getAnnotation(JsonField.class).value();
        if (annotationValue.isEmpty()) {
            return field.getName();
        } else {
            return annotationValue;
        }
    }

    private static String toJsonString(Map<String, String> jsonMap) {
        String elementsString = jsonMap.entrySet()
                .stream()
                .map(entry -> "\"" + entry.getKey() + "\":\"" + entry.getValue() + "\"")
                .collect(Collectors.joining(","));
        return "{" + elementsString + "}";
    }
}
```

```
{"bookName":"Web全栈开发进阶之路","writerName":"沉默王二"}
```

从结果上来看：

- Writer 类的 age 字段没有装饰 `@JsonField` 注解，所以没有序列化
- Writer 类的 name 字段装饰了 `@JsonField` 注解，并且显示指定了字符串“writerName”，所以序列化后变成了 writerName
- Writer 类的 bookName 字段装饰了 `@JsonField` 注解，但没有显式指定值，所以序列化后仍然是 bookName

