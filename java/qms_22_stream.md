# Stream流

单从“Stream”这个单词上来看，它似乎和 java.io包下的 InputStream 和 OutputStream 有些关系。实际上呢，没毛关系。Java 8 新增的 Stream 是为了解放程序员操作集合（Collection）时的生产力，之所以能解放，很大一部分原因可以归功于同时出现的 Lambda 表达式

> Stream 就好像一个高级的迭代器，但只能遍历一次，就好像一江春水向东流；在流的过程中，对流中的元素执行一些操作，比如“过滤掉长度大于 10 的字符串”、“获取每个字符串的首字母”等。

要想操作流，首先需要有一个数据源，可以是数组或者集合。每次操作都会返回一个新的流对象，方便进行链式操作，但原有的流对象会保持不变。

流的操作可以分为两种类型：

- 中间操作，可以有多个，每次返回一个新的流，可进行链式操作。
- 终端操作，只能有一个，每次执行完，这个流也就用光光了，无法执行下一个操作，因此只能放在最后。

中间操作不会立即执行，只有等到终端操作的时候，流才开始真正地遍历，用于映射、过滤等。通俗点说，就是一次遍历执行多个操作，性能就大大提高了。例如：

```java
List<String> list = new ArrayList<>();
list.add("武汉加油");
list.add("中国加油");
list.add("世界加油");
list.add("世界加油");

long count = list.stream().distinct().count();
System.out.println(count);
```

- `distinct()` 方法是一个中间操作（去重），它会返回一个新的流（没有共同元素）。
- `count()` 方法是一个终端操作，返回流中的元素个数。

## 创建流

如果是数组的话，可以使用 `Arrays.stream()` 或者 `Stream.of()` 创建流；如果是集合的话，可以直接使用 `stream()` 方法创建流，因为该方法已经添加到 Collection 接口中。

```java
public class CreateStreamDemo {
    public static void main(String[] args) {
        String[] arr = new String[]{"武汉加油", "中国加油", "世界加油"};
        Stream<String> stream = Arrays.stream(arr);
        
        stream = Stream.of("武汉加油", "中国加油", "世界加油");
        // of() 方法内部其实调用了 Arrays.stream() 方法

        List<String> list = new ArrayList<>();
        list.add("武汉加油");list.add("中国加油");list.add("世界加油");
        stream = list.stream();
    }
}
```

## 操作流

### 过滤

通过 `filter()` 方法可以从流中筛选出我们想要的元素。

```java
public class FilterStreamDemo {
    public static void main(String[] args) {
        List<String> list = new ArrayList<>();
        list.add("周杰伦");list.add("王力宏");list.add("陶喆");list.add("林俊杰");
        Stream<String> stream = list.stream().filter(element -> element.contains("王"));
        stream.forEach(System.out::println);
    }
}
```

`filter()` 方法接收的是一个 Predicate（Java 8 新增的一个函数式接口，接受一个输入参数返回一个布尔值结果）类型的参数，因此，我们可以直接将一个 Lambda 表达式传递给该方法，比如说 `element -> element.contains("王")` 就是筛选出带有“王”的字符串。

`forEach()` 方法接收的是一个 Consumer（Java 8 新增的一个函数式接口，接受一个输入参数并且无返回的操作）类型的参数，`类名 :: 方法名`是 Java 8 引入的新语法，`System.out` 返回 PrintStream 类，println 方法你应该知道是打印的。

### 映射

如果想通过某种操作把一个流中的元素转化成新的流中的元素，可以使用 `map()` 方法。

```java
public class MapStreamDemo {
    public static void main(String[] args) {
        List<String> list = new ArrayList<>();
        list.add("周杰伦");list.add("王力宏");list.add("陶喆");list.add("林俊杰");
        Stream<Integer> stream = list.stream().map(String::length);
        stream.forEach((i) -> System.out.print(i + " "));
    }
}
```

```
3 3 2 3 
```

`map()` 方法接收的是一个 Function（Java 8 新增的一个函数式接口，接受一个输入参数 T，返回一个结果 R）类型的参数，此时参数 为 String 类的 length 方法，也就是把 `Stream<String>` 的流转成一个 `Stream<Integer>` 的流。

### 匹配

Stream 类提供了三个方法可供进行元素匹配，它们分别是：

- `anyMatch()`，只要有一个元素匹配传入的条件，就返回 true。
- `allMatch()`，只有有一个元素不匹配传入的条件，就返回 false；如果全部匹配，则返回 true。
- `noneMatch()`，只要有一个元素匹配传入的条件，就返回 false；如果全部不匹配，则返回 true。

```java
public class MatchStreamDemo {
    public static void main(String[] args) {
        List<String> list = new ArrayList<>();
        list.add("周杰伦");list.add("王力宏");list.add("陶喆");list.add("林俊杰");

        boolean  anyMatchFlag = list.stream().anyMatch(element -> element.contains("王"));
        boolean  allMatchFlag = list.stream().allMatch(element -> element.length() > 1);
        boolean  noneMatchFlag = list.stream().noneMatch(element -> element.endsWith("沉"));
        System.out.println(anyMatchFlag + " " + allMatchFlag + " " + noneMatchFlag);
    }
}
```

因为“王力宏”有“王”字，所以 anyMatchFlag 应该为 true；因为“周杰伦”、“王力宏”、“陶喆”、“林俊杰”的字符串长度都大于 1，所以 allMatchFlag 为 true；因为 4 个字符串结尾都不是“沉”，所以 noneMatchFlag 为 true。

### 组合

`reduce()` 方法的主要作用是把 Stream 中的元素组合起来，它有两种用法：

- `Optional<T> reduce(BinaryOperator<T> accumulator)`：没有起始值，只有一个参数，就是运算规则，此时返回 Optional（提供了一种用于表示可选值而非空引用的类级别解决方案，可避免空指针）

- `T reduce(T identity, BinaryOperator<T> accumulator)`：有起始值，有运算规则，两个参数，此时返回的类型和起始值类型一致

```java
public class ReduceStreamDemo {
    public static void main(String[] args) {
        Integer[] ints = {0, 1, 2, 3};
        List<Integer> list = Arrays.asList(ints);

        // 运算规则可以是 Lambda 表达式，或者类名::方法名
        Optional<Integer> optional = list.stream().reduce((a, b) -> a + b);  
        Optional<Integer> optional1 = list.stream().reduce(Integer::sum);
        System.out.print(optional.orElse(0) + " ");
        System.out.print(optional1.orElse(0) + " ");

        // 有起始值的 reduce
        int reduce = list.stream().reduce(6, (a, b) -> a + b);
        System.out.print(reduce + " ");
        int reduce1 = list.stream().reduce(6, Integer::sum);
        System.out.println(reduce1);
    }
}
```

```java
6 6 12 12
```

## 转换流

`collect()` 方法：既然可以把集合或者数组转成流，那么也应该有对应的方法，将流转换回去

```java
public class CollectStreamDemo {
    public static void main(String[] args) {
        List<String> list = new ArrayList<>();
        list.add("周杰伦");list.add("王力宏");list.add("陶喆");list.add("林俊杰");

        String[] strArray = list.stream().toArray(String[]::new);
        System.out.println(Arrays.toString(strArray));

        List<Integer> list1 = list.stream().map(String::length).collect(Collectors.toList());
        List<String> list2 = list.stream().collect(Collectors.toCollection(ArrayList::new));
        System.out.println(list1);
        System.out.println(list2);

        String str = list.stream().collect(Collectors.joining(", ")).toString();
        System.out.println(str);
    }
}
```

```java
[周杰伦, 王力宏, 陶喆, 林俊杰]
[3, 3, 2, 3]
[周杰伦, 王力宏, 陶喆, 林俊杰]
周杰伦, 王力宏, 陶喆, 林俊杰
```

补充：`String[]::new`，它是什么东东呢？来看一下 `toArray()` 方法的源码。

```java
<A> A[] toArray(IntFunction<A[]> generator);
```

也就是说 `String[]::new` 是一个 IntFunction，一个可以产生所需的新数组的函数，可以通过反编译字节码看看它到底是什么：

```java
String[] strArray = (String[])list.stream().toArray((x$0) -> {
    return new String[x$0];
});
```

也就是相当于返回了一个指定长度的字符串数组。
