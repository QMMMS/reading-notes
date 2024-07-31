# LinkedHashMap和TreeMap

| 特性     | TreeMap        | HashMap        | LinkedHashMap    |
| -------- | -------------- | -------------- | ---------------- |
| 排序     | 支持           | 不支持         | 不支持           |
| 插入顺序 | 不保证         | 不保证         | 保证             |
| 查找效率 | O(log n)       | O(1)           | O(1)             |
| 空间占用 | 通常较大       | 通常较小       | 通常较大         |
| 适用场景 | 需要排序的场景 | 无需排序的场景 | 需要保持插入顺序 |

HashMap 是无序的。如果我们需要一个**有序**的 Map，就要用到 LinkedHashMap，是 HashMap 的子类，它使用链表来记录插入/访问元素的顺序。可以看作是 HashMap + LinkedList 的合体，它使用了哈希表来存储数据，又用了双向链表来维持键值对的插入顺序

TreeMap 由红黑树实现，可以保持元素的自然顺序，或者实现了 Comparator 接口的自定义顺序。

## LinkedHashMap插入顺序

LinkedHashMap 如何维护插入顺序？它并未重写 HashMap 的 `put()` 方法，而是重写了 `put()` 方法需要调用的内部方法 `newNode()`。

这是 HashMap 的。

```java
Node<K,V> newNode(int hash, K key, V value, Node<K,V> next) {
    return new Node<>(hash, key, value, next);
}
```

这是 LinkedHashMap 的。

```java
HashMap.Node<K,V> newNode(int hash, K key, V value, HashMap.Node<K,V> e) {
    LinkedHashMap.Entry<K,V> p =
            new LinkedHashMap.Entry<>(hash, key, value, e);
    linkNodeLast(p);
    return p;
}
```

LinkedHashMap.Entry 继承了 HashMap.Node，并且追加了两个字段 before 和 after，用来维持键值对的关系。

```java
static class Entry<K,V> extends HashMap.Node<K,V> {
    Entry<K,V> before, after;
    Entry(int hash, K key, V value, Node<K,V> next) {
        super(hash, key, value, next);
    }
}
```

在 LinkedHashMap 中，链表中的节点顺序是按照插入顺序维护的。当使用 put() 方法向 LinkedHashMap 中添加键值对时，会将新节点插入到链表的尾部，并更新 before 和 after 属性，以保证链表的顺序关系——由 `linkNodeLast()` 方法来完成：

```java
/**
 * 将指定节点插入到链表的尾部
 *
 * @param p 要插入的节点
 */
private void linkNodeLast(LinkedHashMap.Entry<K,V> p) {
    LinkedHashMap.Entry<K,V> last = tail; // 获取链表的尾节点
    tail = p; // 将 p 设为尾节点
    if (last == null)
        head = p; // 如果链表为空，则将 p 设为头节点
    else {
        p.before = last; // 将 p 的前驱节点设为链表的尾节点
        last.after = p; // 将链表的尾节点的后继节点设为 p
    }
}
```

## LinkedHashMap访问顺序

LinkedHashMap 不仅能够维持插入顺序，还能够维持访问顺序。访问包括调用 `get()` 方法、`remove()` 方法和 `put()` 方法。

要维护访问顺序，需要我们在声明 LinkedHashMap 的时候指定三个参数。

```java
LinkedHashMap<String, String> map = new LinkedHashMap<>(16, .75f, true);
```

第一个参数和第二个参数，指的是初始容量和负载因子。

第三个参数如果为 true 的话，就表示 LinkedHashMap 要维护访问顺序；否则，维护插入顺序。默认是 false。

```java
Map<String, String> linkedHashMap = new LinkedHashMap<>(16, .75f, true);
linkedHashMap.put("沉", "沉默王二");
linkedHashMap.put("默", "沉默王二");
linkedHashMap.put("王", "沉默王二");
linkedHashMap.put("二", "沉默王二");

System.out.println(linkedHashMap);

linkedHashMap.get("默");
System.out.println(linkedHashMap);

linkedHashMap.get("王");
System.out.println(linkedHashMap);
```

```
{沉=沉默王二, 默=沉默王二, 王=沉默王二, 二=沉默王二}
{沉=沉默王二, 王=沉默王二, 二=沉默王二, 默=沉默王二}
{沉=沉默王二, 二=沉默王二, 默=沉默王二, 王=沉默王二}
```

也就是说，最不经常访问的放在头部

> 这种特性可以使用 LinkedHashMap 来实现 LRU 缓存，LRU 是 Least Recently Used 的缩写，即最近最少使用，是一种常用的页面置换算法，选择最近最久未使用的页面予以淘汰。

LinkedHashMap 是如何来维持访问顺序呢？

```java
void afterNodeAccess(Node<K,V> p) { }
void afterNodeInsertion(boolean evict) { }
void afterNodeRemoval(Node<K,V> p) { }
```

`afterNodeAccess()` 会在调用 `get()` 方法的时候被调用，`afterNodeInsertion()` 会在调用 `put()` 方法的时候被调用，`afterNodeRemoval()` 会在调用 `remove()` 方法的时候被调用。

我来以 `afterNodeAccess()` 为例来讲解一下。

```java
/**
 * 在访问节点后，将节点移动到链表的尾部
 *
 * @param e 要移动的节点
 */
void afterNodeAccess(HashMap.Node<K,V> e) { // move node to last
    LinkedHashMap.Entry<K,V> last;
    if (accessOrder && (last = tail) != e) { // 如果按访问顺序排序，并且访问的节点不是尾节点
        LinkedHashMap.Entry<K,V> p = (LinkedHashMap.Entry<K,V>)e, b = p.before, a = p.after;
        p.after = null; // 将要移动的节点的后继节点设为 null
        if (b == null)
            head = a; // 如果要移动的节点没有前驱节点，则将要移动的节点设为头节点
        else
            b.after = a; // 将要移动的节点的前驱节点的后继节点设为要移动的节点的后继节点
        if (a != null)
            a.before = b; // 如果要移动的节点有后继节点，则将要移动的节点的后继节点的前驱节点设为要移动的节点的前驱节点
        else
            last = b; // 如果要移动的节点没有后继节点，则将要移动的节点的前驱节点设为尾节点
        if (last == null)
            head = p; // 如果尾节点为空，则将要移动的节点设为头节点
        else {
            p.before = last; // 将要移动的节点的前驱节点设为尾节点
            last.after = p; // 将尾节点的后继节点设为要移动的节点
        }
        tail = p; // 将要移动的节点设为尾节点
        ++modCount; // 修改计数器
    }
}
```

## TreeMap实现排序

默认情况下，TreeMap 是根据 key 的自然顺序排列的。比如说整数，就是升序，1、2、3、4、5。

```java
TreeMap<Integer,String> mapInt = new TreeMap<>();
mapInt.put(3, "沉默王二");
mapInt.put(2, "沉默王二");
mapInt.put(1, "沉默王二");
mapInt.put(5, "沉默王二");
mapInt.put(4, "沉默王二");

System.out.println(mapInt);
```

```
{1=沉默王二, 2=沉默王二, 3=沉默王二, 4=沉默王二, 5=沉默王二}
```

如果自然顺序不满足，那就可以在声明 TreeMap 对象的时候指定排序规则。

```java
TreeMap<Integer,String> mapIntReverse = new TreeMap<>(Comparator.reverseOrder());  // 或者自定义 Comparator
```

TreeMap 是怎么做到的呢？TreeMap 的 `put()` 方法：

```java
public V put(K key, V value) {
    Entry<K,V> t = root; // 将根节点赋值给变量t
    if (t == null) { // 如果根节点为null，说明TreeMap为空
        compare(key, key); // type (and possibly null) check，检查key的类型是否合法
        root = new Entry<>(key, value, null); // 创建一个新节点作为根节点
        size = 1; // size设置为1
        return null; // 返回null，表示插入成功
    }
    int cmp;
    Entry<K,V> parent;
    // split comparator and comparable paths，根据使用的比较方法进行查找
    Comparator<? super K> cpr = comparator; // 获取比较器
    if (cpr != null) { // 如果使用了Comparator
        do {
            parent = t; // 将当前节点赋值给parent
            cmp = cpr.compare(key, t.key); // 使用Comparator比较key和t的键的大小
            if (cmp < 0) // 如果key小于t的键
                t = t.left; // 在t的左子树中查找
            else if (cmp > 0) // 如果key大于t的键
                t = t.right; // 在t的右子树中查找
            else // 如果key等于t的键
                return t.setValue(value); // 直接更新t的值
        } while (t != null);
    }
    else { // 如果没有使用Comparator
        if (key == null) // 如果key为null
            throw new NullPointerException(); // 抛出NullPointerException异常
            Comparable<? super K> k = (Comparable<? super K>) key; // 将key强制转换为Comparable类型
        do {
            parent = t; // 将当前节点赋值给parent
            cmp = k.compareTo(t.key); // 使用Comparable比较key和t的键的大小
            if (cmp < 0) // 如果key小于t的键
                t = t.left; // 在t的左子树中查找
            else if (cmp > 0) // 如果key大于t的键
                t = t.right; // 在t的右子树中查找
            else // 如果key等于t的键
                return t.setValue(value); // 直接更新t的值
        } while (t != null);
    }
    // 如果没有找到相同的键，需要创建一个新节点插入到TreeMap中
    Entry<K,V> e = new Entry<>(key, value, parent); // 创建一个新节点
    if (cmp < 0) // 如果key小于parent的键
        parent.left = e; // 将e作为parent的左子节点
    else
        parent.right = e; // 将e作为parent的右子节点
    fixAfterInsertion(e); // 插入节点后需要进行平衡操作
    size++; // size加1
    return null; // 返回null，表示插入成功
}
```

既然 TreeMap 的元素是经过排序的，那找出最大的那个，最小的那个，或者找出所有大于或者小于某个值的键来说，就方便多了。

```java
Integer highestKey = mapInt.lastKey();
Integer lowestKey = mapInt.firstKey();

// headMap获取的是到指定 key 之前的 key
Set<Integer> keysLessThan3 = mapInt.headMap(3).keySet();

// tailMap取的是指定 key 之后的 key（包括指定 key）
Set<Integer> keysGreaterThanEqTo3 = mapInt.tailMap(3).keySet();
```

## Comparable和Comparator

TreeMap 中可以自定义使用Comparator，这里聊一聊Comparable和Comparator这两个接口的区别

Comparable 接口的定义：

```java
public interface Comparable<T> {
    int compareTo(T t);
}
```

Comparator 接口的定义：

```java
public interface Comparator<T> {
    int compare(T o1, T o2);
    boolean equals(Object obj);
}
```

- 一个类实现了 Comparable 接口，意味着该类的对象可以直接进行比较（排序），但比较（排序）的方式只有一种，很**单一**。
- 一个类如果想要保持原样，又需要进行不同方式的比较（排序），就可以**定制**比较器（实现 Comparator 接口）。
- Comparable 接口在 `java.lang` 包下，而 `Comparator` 接口在 `java.util` 包下，算不上是亲兄弟，但可以称得上是表（堂）兄弟。

例如，一个类可以实现Comparable 接口，这个类可以直接比较和排序：

```java
public class Cmower implements Comparable<Cmower> {
    private int age;
    private String name;

    public Cmower(int age, String name) {
        this.age = age;
        this.name = name;
    }

    @Override
    public int compareTo(Cmower o) {
        return this.getAge() - o.getAge();
    }

    public static void main(String[] args) {
        Cmower wanger = new Cmower(19,"沉默王二");
        Cmower wangsan = new Cmower(16,"沉默王三");

        if (wanger.compareTo(wangsan) < 0) {
            System.out.println(wanger.getName() + "比较年轻有为");
        } else {
            System.out.println(wangsan.getName() + "比较年轻有为");
        }
    }
}
```

如果我们想让类保持它的原貌，不想主动实现 Comparable 接口，但我们又需要它们之间进行比较，该怎么办呢？可以使用Comparator

```java
public class Cmower  {
    private int age;
    private String name;

    public Cmower(int age, String name) {
        this.age = age;
        this.name = name;
    }
}

// 按照 age 进行比较
public class CmowerComparator implements Comparator<Cmower> {
    @Override
    public int compare(Cmower o1, Cmower o2) {
        return o1.getAge() - o2.getAge();
    }
}

// 按照 name 进行比较
public class CmowerNameComparator implements Comparator<Cmower> {
    @Override
    public int compare(Cmower o1, Cmower o2) {
        if (o1.getName().hashCode() < o2.getName().hashCode()) {
            return -1;
        } else if (o1.getName().hashCode() == o2.getName().hashCode()) {
            return 0;
        }
        return 1;
    }
}
```

在测试类中，可以根据需要选择不同的比较器：

```java
List<Cmower> list = new ArrayList<>();
// ...
list.sort(new CmowerComparator());
list.sort(new CmowerNameComparator());
```

