# 迁移至Java

## 框架

JAVA主类名称：如果你使用Java语言，对于所有的试题，你的主类名称都必须是Main。java 语言中不要使用package语句，代码要求符合JDK1.8的语法规范。

```java
class Main{
    public static void main(String[] args){
        // ...
    }
}
```

## 输入输出

```java
import java.util.Scanner;

//输入
Scanner sc = new Scanner(System.in);
int n=sc.nextInt();
double d=sc.nextDouble();
String str=sc.next();
char c=sc.next().charAt(0);
while(sc.hasNextInt()){
    int n = sc.nextInt();
    System.out.println(n);
}  // Ctrl+D 停止

//输出
System.out.println();
System.out.println(String.format("%04d",4));  //0004（输出规范）
System.out.println(String.format("%04d",11)); //0011
double a = 1.2349;
String a = String.format("%.2f",a);//1.23
```

## Char 常用方法

```java
char ch1 = 'A';
System.out.println(Character.isDigit(ch)); //是否为数字字符
System.out.println(Character.isLetter(ch)); //是否为字母
System.out.println(Character.isLowerCase(ch)); //是否为小写字符
System.out.println(Character.isUpperCase(ch)); //是否为大写字符
System.out.println(Character.toUpperCase(ch)); //转化为大写字符
System.out.println(Character.toLowerCase(ch)); //转化为小写字符
```

```java
ArrayList<Character> mmp = new ArrayList<>();  // 注意装箱
for(int i = 0; i < 10; i++) mmp.add((char)(i + '0'));  // 类似 c++写法，没问题
for(char i = 'A'; i <= 'F'; i++) mmp.add(i);
String line = "";
for(char i : mmp) line+=i;  // 可以直接与String拼接
System.out.println(line);
```

## String 常用方法

```java
int length() 
boolean isEmpty()
char charAt(int index)
String substring(int startIndex, int endIndex)
boolean equals(Object anObject) 
String format(String format, Object... args) 
String trim()  // 去除字符串开头和结尾的空格
String[] split("\\s+");  // 将字符串按照空格分隔成单词数组，可以填其他模式
// String.format("Hello %s %d %.2f", "World", 5, 5.5)
```

> [常用正则表达式](https://github.com/cdoco/learn-regex-zh)

```java
String s1 = "Hello";
String s2 = "World";
String s3 = s1 + " " + s2;  // 拼接

String s4 = s3.replace(" ", "");  // 去掉s3中的空格
String s5 = s4.substring(0, 1) + s4.substring(2);  // 去掉s4中第2个字符
```

```java
Scanner sc = new Scanner(System.in);
String s1 = sc.nextLine();  // 读取一整行

String[] arr = s1.split(" ");  // 以空格分割字符串，存放到数组中
ArrayList<String> list = new ArrayList<>();
for (String s : arr) list.add(s);

int n = Integer.parseInt(list.get(0));  // 字符串转换为整数
int m = Integer.parseInt(list.get(1));
System.out.println(n + m);

String s2 = String.valueOf(n+m);   // int 转换为字符串
String binaryString = Integer.toBinaryString(n);  // 二进制字符串
list.add(s2);
System.out.println(list.get(list.size()-1));
```

```java
char[] arr = s.toCharArray();  // String 转 char[]
Arrays.sort(arr);
String key = new String(arr);  // char[] 转 String
```

> `Arrays.sort(arr)` 是 Java 中的一个静态方法，用于对**数组**进行排序。它可以接受所有的**基本数据类型数组和对象数组**。
>
> `Collections.sort(list)` 也是 Java 中的一个静态方法，但它用于对实现了 `List` 接口的对象进行排序，例如 `ArrayList` 和 `LinkedList`。

## 大数

```java
import java.math.BigDecimal;
import java.math.BigInteger;

//整数
BigInteger a=BigInteger.ONE;
String s1 = sc.next(); //150
String s2 = "2";
BigInteger a = new BigInteger(s1);
BigInteger b = new BigInteger(s2);
System.out.println(a); //150
System.out.println(a.multiply(b));//相乘 300
System.out.println(a.add(b));//相加 152
System.out.println(a.subtract(b));//相减 148
System.out.println(a.divide(b));//相除 75

//小数
BigDecimal a,b；//同上
```

```java
int intMax = Integer.MAX_VALUE; // 2147483647
long longMax = Long.MAX_VALUE;  // 9223372036854775807
```

## Math类

```java
abs(Object o)；
min(Object a, Object b) 
max(Object a, Object b)
pow(double a, double b)
sqrt(double a)
round(float a)
```

## ArrayList

数组：`static int[] father = new int[10000];`

基本操作：

```java
ArrayList<ArrayList<Integer>> mmp = new ArrayList<>();  // 双层数组

// java中只是预留空间，并不会初始化100个String
ArrayList<String> list = new ArrayList<>(100);
for (int i = 0; i < 100; i++) list.add("hello");  // 添加

list.set(0, "world");  // 修改
System.out.println(list.get(0));  // 获取
list.remove(0);  // 移除

// 相互转换
Integer[] array = new Integer[]{1,2,3,4,5};
ArrayList<Integer> arrayList = new ArrayList<>(Arrays.asList(array));
Integer[] array2 = arrayList.toArray(new Integer[0]);
```

自定义排序：

```java
import java.util.ArrayList;

ArrayList<Integer> a = new ArrayList<>(100);
a.add(1);a.add(2);a.add(4);
a.add(5);a.add(3);a.add(7);

a.sort((a, b) -> {
    return b - a;  
    // 如果结果小于0，a优先级大，放前面，在这里就是大的放前面
});

for (int i : a) System.out.println(i);
```

另外一种：

```java
class Student {
    public String name;
    public int age;
    public Student(String name, int age) {
        this.name = name;
        this.age = age;
    }
}

ArrayList<Student> list = new ArrayList<>();
list.add(new Student("Tom", 20));list.add(new Student("Jerry", 18));
list.add(new Student("Alice", 22));list.add(new Student("Bob", 19));

list.sort(new Comparator<Student>() {
    public int compare(Student a, Student b) {
        return a.age - b.age;  // 按年龄升序排列
    }
});

for (Student s : list) System.out.println(s.name + " " + s.age);
```

二分查找：

```java
ArrayList<Integer> list = new ArrayList<>();
list.add(30);list.add(40);list.add(10);
list.add(20);list.add(50);

list.sort((x,y)->{
    return x-y;
});

// 使用binarySearch方法查找元素
int index = Collections.binarySearch(list, 30);

// 输出查找结果，索引位置从0开始
if (index >= 0) System.out.println("元素30在列表中的索引位置为：" + index);
else System.out.println("元素30不在列表中");
```

## 集合

```java
HashSet<Integer> s = new HashSet<>();
boolean result = s.add(12); // 返回一个boolean值，表示是否插入成功
System.out.println(s.size());

boolean found = s.contains(12); // 判断集合中是否包含元素12
System.out.println(found ? 12 : "Not found!");

s.remove(12); // 移除元素12
found = s.contains(12);
System.out.println(found ? 12 : "Not found!");

s.add(123);s.add(2);s.add(1322);

for(int num : s) System.out.print(String.format("%d ", num));
```

## Map

```java
HashMap<String, String> m = new HashMap<>();
m.put("one", "yi");  // 插入键值对 "one" -> "yi"
System.out.println(m.get("one")); // 输出 yi
m.put("one", "1");  // 修改键值对 "one" -> "1"
System.out.println(m.get("one")); // 输出 1

// 查找键 "two"
if (m.containsKey("two")) System.out.println(m.get("two"));
else System.out.println("Not found");

m.remove("one");  // 移除
if (m.containsKey("one")) System.out.println(m.get("one"));
else System.out.println("Not found");
```

```java
map.put(sum, map.getOrDefault(sum, 0) + 1);  // getOrDefault 如果有就取出，没有就取默认值
```

## Queue

```java
import java.util.Queue;
import java.util.LinkedList;

Queue<Integer> q = new LinkedList<>();
q.add(1);q.add(2);
System.out.println(q.poll());  // 返回队首元素并删除
System.out.println(q.peek());  // 返回队首元素
System.out.println(q.size());  // 返回队列大小
```

优先队列：

```java
import java.util.PriorityQueue;

PriorityQueue<Integer> pq = new PriorityQueue<Integer>((a,b) -> b - a); // 大的在前面
pq.add(1);pq.add(2);pq.add(3);
while(!pq.isEmpty()) System.out.println(pq.poll());
```

双向队列（来自单调队列板子）

```java
int[] res = new int[nums.length - k + 1];
Deque<Integer> deque = new LinkedList<>();
for (int i = 0; i < nums.length; i++) {
    if (!deque.isEmpty() && deque.peekFirst() < i - k + 1) {
        deque.pollFirst();
    }
    while (!deque.isEmpty() && nums[deque.peekLast()] < nums[i]) {
        deque.pollLast();
    }
    deque.offerLast(i);
    if (i >= k - 1) {
        res[i - k + 1] = nums[deque.peekFirst()];
    }
}
```



## 其他：swap

C/C++中swap是通过传递变量地址(指针或引用)来交换变量地址中的值。Java对程序员屏蔽了变量地址的概念，为的是减少指针误用。**在Java中函数或者叫方法的入参都是通过值拷贝的方式进行传递**：

- 原始类型(char，int，double等）都是通过直接拷贝变量值传参。`swap(int, int)`不可行；
- 对象类型都是通过引用**拷贝**传参。`swap(Integer, Integer)` 不可行，可以看作我们想改指针，因此需要指针的指针，但是Java不提供。

因此一个替代的实现是：

```java
private static void swap(int a[],int i,int j) {
    int temp=a[i];
    a[i]=a[j];
    a[j]=temp;
}
```

## 综合：[ 十进制转十六进制](https://lx.lanqiao.cn/problem.page?gpid=T49)

```java
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
        ArrayList<Character> mmp = new ArrayList<>();
        ArrayList<Character> ans = new ArrayList<>();
        for(int i = 0; i < 10; i++) mmp.add((char)(i + '0'));
        for(char i = 'A'; i <= 'F'; i++) mmp.add(i);
        
        Scanner sc = new Scanner(System.in);
        int num = sc.nextInt();
        if(num==0) {
        	System.out.print(0);
        	return;
        }
        while(num!=0) {
        	ans.add(mmp.get(num%16));
        	num/=16;
        }
        for(int i=ans.size()-1; i>=0; --i) System.out.print(ans.get(i));
    }
}
```

## 综合：[并查集](https://www.luogu.com.cn/problem/P1551)

```java
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
	static int[] fa = new int[5005];
    
	static int getfa(int x) {
		if(fa[x]==x) return x;
		return fa[x]=getfa(fa[x]);
	}
	
	static void setfa(int son, int father) {
		fa[getfa(son)]=getfa(father);
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		int M = sc.nextInt();
		int P = sc.nextInt();
		
		for(int i = 0; i <= N; ++i) fa[i]=i;
		for(int i = 0; i < M; ++i) {
			int num1 = sc.nextInt();
			int num2 = sc.nextInt();
			setfa(Math.min(num1, num2), Math.max(num1, num2));
		}
		for(int i = 0; i < P; ++i) {
			int num1 = sc.nextInt();
			int num2 = sc.nextInt();
			if(getfa(num1)==getfa(num2)) System.out.println("Yes");
			else System.out.println("No");
		}
	}
}
```

## 综合：树的前序遍历

```java
public class T11 {
    public static void main(String[] args) {
        Tree root = new Tree(1);
        root.left = new Tree(2);
        root.right = new Tree(3);
        root.left.left = new Tree(4);
        root.left.right = new Tree(5);
        root.right.left = new Tree(6);
        root.right.right = new Tree(7);
        root.preOrder(root);
    }
}

class Tree{
    public int val;
    public Tree left;
    public Tree right;
    public Tree(int val){
        this.val = val;
    }

    void preOrder(Tree root){
        if(root == null){
            return;
        }
        System.out.println(root.val);
        preOrder(root.left);
        preOrder(root.right);
    }
}
```

## 综合：dijstra

```java
import java.util.PriorityQueue;
import java.util.Comparator;
import java.util.Scanner;

public class T10 {

    public static int MAX = 10003;
    public static int[] dis = new int[MAX];
    public static int[] vis = new int[MAX];
    public static int[] head = new int[MAX];
    public static Edge[] edge = new Edge[MAX*2];
    public static int cnt = 0;

    public static void addEdge(int u, int v, int w){
        edge[++cnt] = new Edge(v, w);
        edge[cnt].next = head[u];
        head[u] = cnt;
    }

    public static void dijstra(int s){
        for (int i = 0; i < MAX; i++) {
            dis[i] = Integer.MAX_VALUE;
            vis[i] = 0;
        }
        dis[s] = 0;
        PriorityQueue<Node> q = new PriorityQueue<>(new NodeComp());
        q.add(new Node(s, 0));
        while (!q.isEmpty()) {
            Node cur = q.poll();
            int u = cur.pos;
            if (vis[u] == 1) {
                continue;
            }
            vis[u] = 1;
            for (int i = head[u]; i != 0; i = edge[i].next) {
                int v = edge[i].to;
                int w = edge[i].dis;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    q.add(new Node(v, dis[v]));
                }
            }
        }
    }


    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N, M, u, v, w;
        N = sc.nextInt();
        M = sc.nextInt();
        for (int i = 0; i < M; i++) {
            u = sc.nextInt();
            v = sc.nextInt();
            w = sc.nextInt();
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        dijstra(1);
        for (int i = 1; i <= N; i++) {
            System.out.println(dis[i]);
        }
    }
}

class Node{
    public int pos;
    public int dis;
    public Node(int pos, int dis) {
        this.pos = pos;
        this.dis = dis;
    }
}

class NodeComp implements Comparator<Node> {
    @Override
    public int compare(Node a, Node b) {
        return a.dis - b.dis;  // 按距离升序排列
    }
}

class Edge{
    public int to;
    public int dis;
    public int next;
    public Edge(int to, int dis) {
        this.to = to;
        this.dis = dis;
    }
}
```

