# 线性结构

## 链表

### 单链表倒置

倒置一个不带头节点的单链表。

```cpp
Node* Reverse(Node* first) {
    Node* p = first->next;//p走在最前面
    Node* q = first;//q随p后
    Node* r = NULL;//r最后
    
    while (p != NULL) {
        q->next = r;//反转操作
        
        r = q;//p，q，r都向前走一步
        q = p;
        p = p->next;
    }
    q->next = r;//最后一步反转
    return q;
}
```

## 栈

### 出栈序列

给定一个长度为 $n$ 的入栈序列，所有可能的出栈序列数量为：
$$
N=\frac{C^{n}_{2n}}{n+1}
$$
给定一个入栈序列，判断一个序列是否为出栈序列：

如果入栈序列依次增大，例如1,2,3,4,5，如果出现大的数字，那么之后小的数字必须反过来。就像4,5,3,2,1这个出栈序列，4已经第一个出现，比它小的1,2,3是反过来的

### 数制转换

**任务：**

将一个十进制数转换为$k$进制数。

**思想：**

将整数$N$一直除以$k$，余数进栈，商作为下一个$N$，输出时会反着输出（因为栈）。

**代码：**

```cpp
void baseTrans(int N, int k) {
    stack<int> s;
    while(N){
        s.push(N % k);
        N /= k;
    }
    while(!s.empty()){
        cout << s.top();
        s.pop();
    }
    cout << endl;
}
```

### 后缀表达式

### 中缀表达式

### 中缀表达式转化为后缀表达式

*TODO：计算后缀表达式，中缀表达式，后缀与中缀的转化*

## 字符串

## KMP匹配

**任务：**

给定一个字符串(长度为 $n$ )和一个模式串(长度为 $m$ )，找出模式串在字符串中出现的位置，要求时间复杂度接近 $$O(n+m)$$

**分析：**

朴素的想法是字符串从前往后每个位置去匹配模式串，这样的时间复杂度为$$O(n*m)$$

当中很多时候匹配失败，这些信息不应该被简单忽略，KMP尝试利用失败的匹配步骤

比如字符串匹配到位置 10 不再匹配，其实意味着位置 9 和之前的字符都匹配

如果模式串后面 3 个和最前面 3 个又相同，由相等传递，模式串的最前面 3 个和字符串最后面 3 个匹配

已经匹配的部分不用重新检查，直接向后继续匹配，这样减少了很多步骤

那么对于模式串每个位置，怎么快速找到与最前面一段相同的长度？

用 $kmp$ 数组表示每个位置对应的长度，在处理位置 $5$ 时，位置 $4$ 已经处理好了（找到了与最前面一段相同的长度），那么从位置 $4$ 指示的长度+1找起，若相同则 $$kmp[5]=kmp[4]+1$$ 

如果不等，就从位置 $4$ 指示的最前面一段子串找起，$$kmp[5]=kmp[kmp[4]-1]+1$$ ，一直到找到或为 0 

> 例子：
>
> ```
> 	0 1 2 3 4 5 6
> B = a b a b a c b
> P = 0 0 1 2 3 ?
> ```
>
> 位置 $4$ 指示的最前面一段子串是`a b a`

>   另外一个例子：
>
>   ```
>   a b c a a b b c a b c a a b d a b
>   0 0 0 1 1 2 0 0 1 2 3 4 5 6 0 1 2
>   ```

**核心代码：**

```cpp
int kmp[MAX];

void pre_kmp(string P) {
	kmp[0] = 0;
	for (int i = 1; i < P.size(); ++i) {
		int k = kmp[i - 1];
		while (k > 0 && P[i] != P[k]) k = kmp[k - 1]; //如果不等，从子串找起
		if (P[i] == P[k]) kmp[i] = k + 1;
		else kmp[i] = 0;//k = 0
	}
}

int KMP(string T, string P, int pos) {
	if (T.size() - P.size() < pos) return -1;
	int i = pos, j = 0;
	while (i < T.size() && j < P.size()) {
		if (T[i] == P[j]) i++, j++;
		else if (j) j = kmp[j - 1];//已经匹配的部分不用重新检查
		else i++;
	}
	if (j == P.size()) return i - j;
	else return -1;
}
```

> 练练手？洛谷P3375 【模板】KMP字符串匹配
>
> https://www.luogu.com.cn/problem/P3375
>
> 提示：使用C风格字符数组，输入输出用cstdio

>   STL?
>
>   ```cpp
>   string s = "hello world";
>   int index = s.find("hello");//0
>   ```

## STL常用容器操作

### set

```cpp
#include<iostream>
#include<set>
#include<string>
using namespace std;

int main() {
    set<int> s;
    pair<set<int>::iterator, bool> result = s.insert(12); // 返回一个pair，第一个元素是一个迭代器，指向插入的元素，第二个元素是一个bool值，表示是否插入成功
    cout << *result.first << " " << result.second << endl;
    cout << s.size() << endl;
    set<int>::iterator it = s.find(12); // 返回一个迭代器，指向元素12，如果没有找到，返回end()
    cout << *it << endl;
    s.erase(12);
    it = s.find(12);
    if (it == s.end()) cout << "Not found!" << endl;

    return 0;
}
```

C++ 11 为 STL 标准库增添了 4 种无序(哈希)容器，可以使用无序set，例如：

```cpp
#include<unordered_set>
unordered_set<int> us;
```

其余用法与传统set一致。

### map

```cpp
#include<iostream>
#include<map>
#include<string>
using namespace std;

int main() {
    map<string, string> m;
    pair<map<string, string>::iterator, bool> ret = m.insert(make_pair("one", "what?")); // 返回一个pair，第一个元素是一个迭代器，指向插入的元素，第二个元素是一个bool值，表示是否插入成功
    cout << ret.first->first << " " << ret.first->second << " " << ret.second << endl;
    m["one"] = "yi";
    cout << m["one"] << endl;

    map<string, string>::iterator it = m.find("onee"); // 返回一个迭代器，指向元素，如果没有找到，返回end()
    if (it == m.end())cout << "Not found!" << endl;
    it = m.find("one");
    if (it != m.end())cout << it->first << " " << it->second << endl;

    m.erase("one");
    it = m.find("one");
    if (it == m.end())cout << "Not found!" << endl;

    return 0;
}
```

### lower_bound/upper_bound/sort/自定义规则

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    vector<int> nums = {2,43,1,3,2,3,41,};
    sort(nums.begin(), nums.end());
    for(int i : nums) cout << i << " ";
    cout << endl;
    //upper_bound返回第一个大于x的数的位置
    cout << upper_bound(nums.begin(), nums.end(), 3) - nums.begin() << endl;
    //lower_bound返回第一个大于等于x的数的位置
    cout << lower_bound(nums.begin(), nums.end(), 3) - nums.begin() << endl;
    return 0;
}
```

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class TestObj {
public:
	int first;
	double second;
	TestObj(int f, double s) :first(f), second(s) {}
	bool operator<(const TestObj& that) const {
		return this->second < that.second;
	}
};

vector<TestObj> v;

int main() {
	for (int i = 10; i > 0 ; --i) v.push_back(TestObj(i, 1 * i * i * i - 4 * i * i + 10 * i - 100));
	for (int i = 0; i < 10; ++i) cout << v[i].first << " " << v[i].second << endl;
	cout << endl << endl;
	sort(v.begin(), v.end());
	for (int i = 0; i < 10; ++i) cout << v[i].first << " " << v[i].second << endl;
	cout << endl << endl;
	vector<TestObj> ::iterator it = lower_bound(v.begin(), v.end(), TestObj(1, -25));
	cout << it->first << " " << it->second << endl;
	it = upper_bound(v.begin(), v.end(), TestObj(1, -25));
	cout << it->first << " " << it->second << endl;

	return 0;
}
```

```cpp
map<string, vector<record>> records;
for(auto it=records.begin(); it!=records.end(); it++){
    sort(it->second.begin(), it->second.end(), [](record a, record b){
        if(a.day != b.day) return a.day < b.day;
        if(a.hour != b.hour) return a.hour < b.hour;
        return a.minute < b.minute;
    });  // 这里的 sort 函数是一个lambda函数，用来对每个人的记录进行排序
}
```

```cpp
sort(v1positive.begin(), v1positive.end(), greater<int>());  // 大的在前
sort(v1negative.begin(), v1negative.end(), less<int>());  // 小的在前
```

```cpp
#define pq priority_queue<int, vector<int>, greater<int>>
```

### 其他常用方法

**批量内存（数组）设置**

```cpp
#include<cstring>
a[123][4342][123][234];
memset(a,0,sizeof(a));
memset(a,0x3f,sizeof(a));//初始化为无穷大
memset(a,63, sizeof(a));//初始化为无穷大，与上一行效果一样
```

**不定长输入**

```cpp
int a[MAX],num;
while(cin>>num) a[++N]=num;//输入EOF使用Ctrl+D
```

**字符串与数的转换**

```cpp
#include<string>
int num = 1000;
string s = to_string(num);
int i = stoi(s.substr(0, 3));
double d = stod(s);
```

**预留vector空间**

```cpp
vector<int> dp(1000);
vector<vector<int>> children(103, vector<int>());
```

**读取一整行**

```cpp
string line;
getline(cin, line);
```

警告，getline很容易出现bug（因为linux与windows不同的换行标准），不要普通的 cin >> 和getline 混用

**快读**

```cpp
inline int read()
{
    char c = getchar();int x = 0,s = 1;
    while(c < '0' || c > '9') {if(c == '-') s = -1;c = getchar();}//是符号
    while(c >= '0' && c <= '9') {x = x*10 + c -'0';c = getchar();}//是数字
    return x*s;
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);//加速器
    int n = read();
    cout << n << endl;
    return 0;
}
```

**分割字符串**

```cpp
vector<string> spilt(string str, string pattern){
    vector<string> res;
    if(pattern.empty()) return res;
    int start = 0, index = str.find_first_of(pattern, 0); 
    // find_first_of()返回第一个匹配的位置，两个参数分别是要查找的字符串和开始查找的位置
    while(index != str.npos){
        // str.nops是string类的一个静态成员，表示不存在的位置
        if(start != index){
            res.push_back(str.substr(start, index - start));
        }
        start = index + 1;
        index = str.find_first_of(pattern, start);
    }
    if(!str.substr(start).empty()){
        res.push_back(str.substr(start));
    }
    return res;
}
```

字符串常用方法：

```cpp
#include<string>
#include<algorithm>
using namespace std;

string s = "hello world 34";
cout << isdigit(s[12]) << endl;  // 1
reverse(s.begin(), s.end());  // 反转
cout << s << endl;  // 43 dlrow olleh
cout << s.substr(3, 5) << endl;  // dlrow，从第三个char开始后的5个char
```

## 杂题思路

> 大部分来自力扣热题100

给定一个整数数组 `nums` 和一个整数目标值 `target`，请你在该数组中找出 **和为目标值** *`target`* 的那 **两个** 整数，并返回它们的数组下标。（思路：哈希表保存值和下标）

------

给你一个字符串数组，请你将 **字母异位词**（重新排列源单词的所有字母得到的一个新单词） 组合在一起。可以按任意顺序返回结果列表。（思路：哈希表保存key和对应列表，将每个字母出现的次数使用字符串表示，作为哈希表的键）

------

给定一个未排序的整数数组 `nums` ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。例如，nums = [100,4,200,1,3,2]，最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。（思路：set保存值，最后遍历一遍）

------

给定一个长度为 `n` 的整数数组 `height` 。有 `n` 条垂线，第 `i` 条线的两个端点是 `(i, 0)` 和 `(i, height[i])` 。找出其中的两条线，使得它们与 `x` 轴共同构成的容器可以容纳最多的水。

![](./pic/question_11.jpg)

思路：双指针，每次移动 **数字较小的那个指针**。

------

给你一个整数数组 `nums` ，判断是否存在三元组 `[nums[i], nums[j], nums[k]]` 满足 `i != j`、`i != k` 且 `j != k` ，同时还满足 `nums[i] + nums[j] + nums[k] == 0` 。请你返回所有和为 `0` 且不重复的三元组。

思路：排序，遍历第一个元素，然后双指针，一个从前向后，一个从后向前

------

给定一个字符串 `s` ，请你找出其中不含有重复字符的 **最长 子串** 的长度。

思路：维护一个双指针维护的滑动窗口，使用 set 来判断是否含有重复字符

------

以数组 `intervals` 表示若干个区间的集合，其中单个区间为 `intervals[i] = [starti, endi]` 。请你合并所有重叠的区间，并返回 *一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间* 。

思路：如果我们按照区间的左端点排序，那么在排完序的列表中，可以合并的区间一定是连续的。

------

给定一个整数数组 `nums`，将数组中的元素向右轮转 `k` 个位置，其中 `k` 是非负数。

思路：当我们将数组的元素向右移动 *k* 次后，尾部 *k*mod*n* 个元素会移动至数组头部，其余元素向后移动 *k*mod*n* 个位置。

我们以 n=7，k=3 为例进行如下展示：

1. 原始数组	1 2 3 4 5 6 7
2. 翻转所有元素	7 6 5 4 3 2 1
3. 翻转 [0,kmodn−1] 区间的元素	5 6 7 4 3 2 1
4. 翻转 [kmodn,n−1] 区间的元素	5 6 7 1 2 3 4

