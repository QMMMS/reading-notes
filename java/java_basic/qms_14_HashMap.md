# HashMap

HashMap 是 Java 中常用的数据结构之一，用于存储键值对。在 HashMap 中，每个键都映射到一个唯一的值，可以通过键来快速访问对应的值，算法时间复杂度可以达到 O(1)。

HashMap 在遍历时是无序的，因此如果需要有序遍历，可以使用TreeMap

> 在实际应用中，HashMap 可以用于缓存、索引等场景。例如，可以将用户 ID 作为键，用户信息作为值，将用户信息缓存到 HashMap 中，以便快速查找。又如，可以将关键字作为键，文档 ID 列表作为值，将文档索引缓存到 HashMap 中，以便快速搜索文档。

HashMap 的实现原理是基于哈希表的，它的底层是一个数组，数组的每个位置可能是一个链表或红黑树，也可能只是一个键值对。

- 当添加一个键值对时，HashMap 会根据键的哈希值计算出该键对应的数组下标（索引），然后将键值对插入到对应的位置。
- 当通过键查找值时，HashMap 也会根据键的哈希值计算出数组下标，并查找对应的值。

## hash 方法

hash 方法的主要作用是将 key 的 hashCode 值进行处理，得到最终的哈希值。由于 key 的 hashCode 值是不确定的，可能会出现哈希冲突，因此需要将哈希值通过一定的算法映射到 HashMap 的实际存储位置上。

```java
// JDK 8
static final int hash(Object key) {
    int h;
    return (key == null) ? 0 : (h = key.hashCode()) ^ (h >>> 16);
}
```

- 如果键值为 null，则哈希码为 0，则存放在第一个位置
- 否则，通过调用`hashCode()`方法获取键的哈希码，并将其与右移 16 位的哈希码进行异或运算

![](./img/hash-01.png)

**hash 方法是用来做哈希值优化的**，把哈希值右移 16 位，也就正好是自己长度的一半，之后与原哈希值做异或运算，这样就混合了原哈希值中的高位和低位，增大了随机性。让数据元素更加均衡的分布，减少碰撞。

下一步，put与get将新的哈希值取模（mod），得到一个实际的存储位置。这个取模操作的目的是将哈希值映射到桶（Bucket）的索引上，桶是 HashMap 中的一个数组，每个桶中会存储着一个链表（或者红黑树），装载哈希值相同的键值对（没有相同哈希值的话就只存储一个键值对）。

## hashCode 方法

那么`hashCode()`方法又是怎么实现的呢？我们在 String 一节已经介绍过它的 `hashCode()` 方法了：

```java
private int hash; // 缓存字符串的哈希码

public int hashCode() {
    int h = hash; // 从缓存中获取哈希码
    // 如果哈希码未被计算过（即为 0）且字符串不为空，则计算哈希码
    if (h == 0 && value.length > 0) {
        char val[] = value; // 获取字符串的字符数组

        // 遍历字符串的每个字符来计算哈希码
        for (int i = 0; i < value.length; i++) {
            h = 31 * h + val[i]; // 使用 31 作为乘法因子
        }
        hash = h; // 缓存计算后的哈希码
    }
    return h; // 返回哈希码
}
```

31 倍哈希法（31-Hash）是一种简单有效的字符串哈希算法，常用于对字符串进行哈希处理。该算法的基本思想是将字符串中的每个字符乘以一个固定的质数 31 的幂次方，并将它们相加得到哈希值：

$$
H(s) = (s[0] \times 31^{n-1}) + (s[1] \times 31^{n-1}) + ... + (s[n-1] \times 31^0)
$$
31 倍哈希法的优点在于简单易实现，计算速度快，同时也比较均匀地分布在哈希表中。

类似的，Objects 类的 `hash()` 方法可以针对不同数量的参数生成新的 `hashCode()` 值：

```java
public static int hashCode(Object a[]) {
     if (a == null)
         return 0;
     int result = 1;
     for (Object element : a)
         result = 31 * result + (element == null ? 0 : element.hashCode());
     return result;
}
```

$$
H(a)=(a[0] \times 31^{n-1}) + (a[1] \times 31^{n-1}) + ... + (a[n-1] \times 31^0)
$$

我们来分析一段代码：

```java
public class Test {
    public static void main(String[] args) {
        Student s1 = new Student(18, "张三");
        Map<Student, Integer> scores = new HashMap<>();
        scores.put(s1, 98);
        System.out.println(scores.get(new Student(18, "张三")));
    }
}
 class Student {
    private int age;
    private String name;

     public Student(int age, String name) {
         this.age = age;
         this.name = name;
     }

     @Override
     public boolean equals(Object o) {
         Student student = (Student) o;
         return age == student.age &&
                 Objects.equals(name, student.name);
     }
 }
```

```
null
```

奇怪！我们明明把`Student(18, "张三")`塞进HashMap 中了，为什么get的时候又找不到？

原因就在于重写 `equals()` 方法的时候没有重写 `hashCode()` 方法。默认情况下，`hashCode()` 方法是一个本地方法，会**返回对象的存储地址**，显然 `put()` 中的 s1 和 `get()` 中的 `new Student(18, "张三")` 是两个对象，它们的存储地址肯定是不同的。

> - 如果两个对象调用 `equals()` 方法得到的结果为 true，调用 `hashCode()` 方法得到的结果必定相等；
> - （等价逆否命题）如果两个对象调用 `hashCode()` 方法得到的结果不相等，调用 `equals()` 方法得到的结果必定为 false；
> - 反之则不一定

虽然HashMap 的 `get()` 方法会在外面套一层，调用 `hash(key.hashCode())` 计算对象的哈希值，虽然两个不同的 `hashCode()` 结果经过 `hash()` 方法计算后有可能得到相同的结果，但这种概率微乎其微。

怎么解决这个问题呢？很简单，重写 `hashCode()` 方法。

```java
 @Override
 public int hashCode() {
     return Objects.hash(age, name);
 }
```

设计 `hashCode()` 时最重要的因素就是：无论何时，对同一个对象调用 `hashCode()` 都应该生成同样的值。如果在将一个对象用 `put()` 方法添加进 HashMap 时产生一个 `hashCode()` 值，而用 `get()` 方法取出时却产生了另外一个 `hashCode()` 值，那么就无法重新取得该对象了。

所以，如果你的 `hashCode()` 方法依赖于对象中易变的数据，用户就要当心了，因为此数据发生变化时，`hashCode()` 就会生成一个不同的哈希值，相当于产生了一个不同的键。也就是说，如果在重写 `hashCode()` 和 `equals()` 方法时，对象中某个字段容易发生改变，那么最好舍弃这些字段，以免产生不可预期的结果。

## put与get

**put 的时候计算下标，把键值对放到对应的桶上**。

```java
public V put(K key, V value) {
    return putVal(hash(key), key, value, false, true);
}

final V putVal(int hash, K key, V value, boolean onlyIfAbsent, boolean evict) {
    HashMap.Node<K,V>[] tab;  // 数组
    HashMap.Node<K,V> p;   // 元素

    int n, i;  // n 为数组的长度 i 为下标
    if ((tab = table) == null || (n = tab.length) == 0)
        // 数组为空的时候, 第一次扩容后的数组长度
        n = (tab = resize()).length;
    // 计算节点的插入位置，如果该位置为空，则新建一个节点插入
    if ((p = tab[i = (n - 1) & hash]) == null)
        tab[i] = newNode(hash, key, value, null);
}
```

理论上，哈希值（哈希码）是一个 int 类型，范围从-2147483648 到 2147483648。前后加起来大概 40 亿的映射空间，只要哈希值映射得比较均匀松散，一般是不会出现哈希碰撞（哈希冲突会降低 HashMap 的效率）。

但问题是一个 40 亿长度的数组，内存是放不下的。HashMap 扩容之前的数组初始大小只有 16，所以这个哈希值是不能直接拿来用的，用之前要和数组的长度做与运算，用得到的值来访问数组下标才行。

> 为什么用与而不是余？在计算机中，位运算`&`的速度要远高于取余运算`%`，因为计算机本质上就是二进制嘛。

get类似，**get 的时候通过下标，把键值对从对应的桶上取出来**

```java
final Node<K,V> getNode(int hash, Object key) {
    // 获取当前的数组和长度，以及当前节点链表的第一个节点（根据索引直接从数组中找）
    Node<K,V>[] tab;
    Node<K,V> first, e;
    int n;
    K k;
    if ((tab = table) != null && (n = tab.length) > 0 &&
            (first = tab[(n - 1) & hash]) != null) {
        // 如果第一个节点就是要查找的节点，则直接返回
        if (first.hash == hash && ((k = first.key) == key || (key != null && key.equals(k))))
            return first;
        // 如果第一个节点不是要查找的节点，则遍历节点链表查找
        if ((e = first.next) != null) {
            do {
                if (e.hash == hash && ((k = e.key) == key || (key != null && key.equals(k))))
                    return e;
            } while ((e = e.next) != null);
        }
    }
    
    return null;  // 没有找到对应的节点
}
```

## 扩容机制

类似ArrayList这种“动态数组”可以自动扩容，HashMap 的底层用的也是数组。向 HashMap 里不停地添加元素，当数组无法装载更多元素时，就需要对数组进行扩容，以便装入更多的元素；

1. 当元素数量达到负载因子（load factor）乘以数组长度时，开始扩容
2. 扩容操作时，HashMap 会先将数组的长度扩大一倍
3. 然后将原来的元素重新散列到新的数组中
4. 元素的位置是通过 key 的 hash 和数组长度进行与运算得到的，因此在数组长度扩大后，元素的位置也会发生一些改变。一部分索引不变，另一部分索引为“原索引+旧容量”

容量的提升也会相应地提高查询效率，因为“桶（坑）”更多了嘛，原来需要通过链表存储的（查询的时候需要遍历），扩容后可能就有自己专属的“坑位”了（直接就能查出来）。

```java
// JDK 7
// newCapacity为新的容量
void resize(int newCapacity) {
    Entry[] oldTable = table;  // 小数组，临时过度下
    int oldCapacity = oldTable.length;   // 扩容前的容量
    // MAXIMUM_CAPACITY 为最大容量，2 的 30 次方 = 1<<30
    if (oldCapacity == MAXIMUM_CAPACITY) {
        // 容量调整为 Integer 的最大值 0x7fffffff（十六进制）=2 的 31 次方-1
        threshold = Integer.MAX_VALUE;
        return;
    }

    // 初始化一个新的数组（大容量）
    Entry[] newTable = new Entry[newCapacity];
    // 把小数组的元素转移到大数组中
    transfer(newTable, initHashSeedAsNeeded(newCapacity));
    // 引用新的大数组
    table = newTable;
    // 重新计算阈值
    threshold = (int)Math.min(newCapacity * loadFactor, MAXIMUM_CAPACITY + 1);
}
```

newCapacity 是如何计算的呢？

```java
int newCapacity = oldCapacity * 2;  // 两倍

// 避免新容量太小或太大
if (newCapacity < 0 || newCapacity >= MAXIMUM_CAPACITY) {
    newCapacity = MAXIMUM_CAPACITY;
} else if (newCapacity < DEFAULT_INITIAL_CAPACITY) {
    newCapacity = DEFAULT_INITIAL_CAPACITY;
}
```

如何转移？

```java
void transfer(Entry[] newTable, boolean rehash) {
    int newCapacity = newTable.length;  // 新的容量
    // 遍历小数组
    for (Entry<K,V> e : table) {
        while(null != e) {
            Entry<K,V> next = e.next;  // 拉链法，相同 key 上的不同值
            
            if (rehash) {  // 是否需要重新计算 hash
                e.hash = null == e.key ? 0 : hash(e.key);
            }
            // 根据大数组的容量，和键的 hash 计算元素在数组中的下标
            int i = indexFor(e.hash, newCapacity);
            e.next = newTable[i];  // 同一位置上的新元素被放在链表的头部
            newTable[i] = e;  // 放在新的数组上
            e = next;  // 链表上的下一个元素
        }
    }
}
```

注意，`e.next = newTable[i]`，也就是使用了单链表的头插入方式，同一位置上新元素总会被放在链表的头部位置；这样先放在一个索引上的元素最终会被放到链表的尾部，这就会导致在旧数组中同一个链表上的元素，通过重新计算索引位置后，有可能被放到了新数组的不同位置上。

定位元素位置的代码是这样的，相当于用键的哈希值和数组大小取模：

```java
static int indexFor(int h, int length) {
    // assert Integer.bitCount(length) == 1 : "length must be a non-zero power of 2";
    return h & (length-1);
}
```

## 加载因子为什么是 0.75

HashMap 是用数组+链表/红黑树实现的，我们要想往 HashMap 中添加数据（元素/键值对）或者取数据，就需要确定数据在数组中的下标（索引）

1. 先把数据的键进行一次 hash` (key == null) ? 0 : (h = key.hashCode()) ^ (h >>> 16)`
2. 再做一次取模运算确定下标`i = (n - 1) & hash`

**加载因子**是用来表示 HashMap 中数据的填满程度：填入哈希表中的数据个数 / 哈希表的长度。当当 HashMap 的数组长度达到一个**临界值**（ 初始容量 * 加载因子）的时候，就会触发扩容

容易产生两个问题，需要在两个问题中找到平衡：

- 加载因子越大，数组的容量过小，经过哈希计算后的下标，容易出现冲突；
- 加载因子越小，数组的容量过大，导致空间利用率不高。

**为什么加载因子会选择 0.75 呢？为什么不是 0.8、0.6 呢**？

我们设HashMap长度为s，如果我们使用一个足够好的哈希函数，那么put到每一个坑位上的概率都是$$\frac{1}{s}$$，设我们put了n次，如果一次碰撞都没有的概率大于等于0.5，那么我们认为性能优秀，即：
$$
(1-\frac{1}{s})^{n} \geq 0.5
$$
这时候，我们对于该公式其实最想求的时候长度s的时候，n为多少次就应该进行扩容了？而负载因子则是$$n/s$$的值。
$$
\frac{n}{s} \leq \lim_{s\to \inf} \frac{\ln 2}{s\ln \frac{s}{s-1}} \sim \ln2 \sim 0.693
$$
然后再去考虑hashmap一些内置的要求，乘16可以最好一个整数，我们取0.75

## 线程不安全

三方面原因：

**多线程下扩容会死循环**：JDK 7 时，采用的是头部插入的方式来存放链表的，也就是下一个冲突的键值对会放在上一个键值对的前面。扩容的时候，加上多线程，就有可能导致出现环形链表，造成死循环。不过，JDK 8 时已经修复了这个问题，扩容时会保持链表原来的顺序。

**多线程下 put 会导致元素丢失**：多线程同时执行 put 操作时，如果计算出来的索引位置是相同的，那会造成前一个 key 被后一个 key 覆盖，从而导致元素的丢失。

**put 和 get 并发时会导致 get 到 null**：线程 1 执行 put 时，因为元素个数超出阈值而导致出现扩容，线程 2 此时执行 get，就有可能出现这个问题

为了解决这个问题，Java 提供了线程安全的 HashMap 实现类 ConcurrentHashMap。ConcurrentHashMap 内部采用了分段锁（Segment），将整个 Map 拆分为多个小的 HashMap，每个小的 HashMap 都有自己的锁，不同的线程可以同时访问不同的小 Map，从而实现了线程安全。在进行插入、删除和扩容等操作时，只需要锁住当前小 Map，不会对整个 Map 进行锁定，提高了并发访问的效率
