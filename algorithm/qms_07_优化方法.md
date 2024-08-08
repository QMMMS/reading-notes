# 优化方法

## 重新思考排序

**任务：**

给定一组数字段，连接成最小的数字。例如，给定{32，321，3214，0229，87}，我们可以连接成许多数字，例如32-321-3214-0229-87或0229-32-87-321-3214，关于这些片段的不同组合顺序，最小的数字是0229-321-3214-32-87。

**分析：**

朴素的贪心的思考方式应该是：首先给我两个数字段，例如32和321，我把它们正反组合排列起看哪个更小来排序，在这个例子中是 32-132，然后再拿到3214，在两个数中间的三个空之间插入排序，把3214插入进去。

众所周知，插入排序是很慢的，我们能不能使用快速排序来书写？这里我们遇到了一个困境：我们目前的方式是在每个空位插入一个新的数字段，然后看整个数字哪个最小。而传统的cmp函数方法要求我们随便拿出两个元素出来就要比大小。

我们重新审视排序过程：我们真的需要把整个数字拿出来比较吗？其实我们可以看作把前面和后面的数字固定不动，只比较要插入的这个数字段和我们要比较的数字段，即：

```cpp
bool cmp(string a, string b){
    return a + b < b + a;
}
```

**代码：**

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
vector<string> nums;
int N;
int main(){
    cin >> N;
    string s;
    for(int i = 0; i < N; i++){
        cin >> s;
        nums.push_back(s);
    }
    sort(nums.begin(), nums.end(), [](string a, string b){return a + b < b + a;});
    string ans = "";
    for(int i = 0; i < N; i++)ans += nums[i];
    while(ans.size()!=0 && ans[0] == '0')ans.erase(ans.begin());
    if(ans.size() == 0)cout << 0;
    else cout << ans;
    return 0;
}
```

> 来源：PAT甲级 **1038 Recover the Smallest Number**

## 二分

**任务：**

你找到一本残缺很多但还是很厚的词典，想找到某个词或确认它不在，要求时间复杂度$O(log \ n)$

**分析：**

词典意味着**有序**

先翻到词典中间，与要找的词比较，让查找范围缩小一半

重复操作，一直到找到

**核心代码：**

```cpp
int l=1,r=MAX,mid=(l+r)>>1;//准备开始二分
while(l <= r){//终止条件
	//使用judge函数来判断当前猜测的答案是否可行
    if(judge(mid)){//如果可以的话 
        r = mid - 1;//改变右端点，看看再少一点是不是也可以
        mid = (l + r) >> 1;
    } else{
        l = mid + 1;//当前答案不可行，需要增大答案
        mid = (l + r) >> 1;
    }
}
cout << l << endl;//输出找到的答案
```

> 看到最大的最小（最小的最大），可能是二分或者二分答案

std::lower_bound() 返回有序表里第一个大于等于给定值的指针或迭代器；

std::upper_bound() 返回有序表里第一个大于给定值的指针或迭代器；

set / map / … （迭代器是不可减）用法：

```cpp
a.lower_bound(2)
```

vector （迭代器是可以减的）用法：

```cpp
lower_bound(a.begin(), a.end(), 2)
```

## 二维前缀和

**任务：**

给出一个 $n * n$ 矩阵，从中找到最大加权矩形。

**分析：**

朴素的想法是对所有可能的矩形都做一遍遍历，但是要枚举所有矩形，时间复杂度已经达到 $O(n^4)$，再遍历矩形求权，时间复杂度最终达到 $O(n^6)$

前缀和的思想是记录数组中从开始到当前值的和，做一遍预处理，以应对之后对于和的询问。对于这个任务，可以让时间复杂度保留在 $O(n^4)$

二维前缀和记录左上角顶点为$(0,0)$，右下角顶点为$(i,j)$矩阵的权，递推式为：
$$
f[i][j]=a[i][j]+f[i-1][j]+f[i][j-1]-f[i-1][j-1]
$$
**代码：**

>   例题：洛谷P1719 最大加权矩形
>
>   https://www.luogu.com.cn/problem/P1719

```cpp
#include<iostream>
#include<cmath>
using namespace std;

int a[200][200];
int f[200][200];
int N, ans;

int main() {
	cin >> N;
	for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) cin >> a[i][j];
	for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) f[i][j] = a[i][j] + f[i][j - 1] + f[i - 1][j] - f[i - 1][j - 1];
	for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) for (int x = i; x <= N; ++x) for (int y = j; y <= N; ++y) ans = max(ans, f[x][y] - f[i - 1][y] - f[x][j - 1] + f[i - 1][j - 1]);
	cout << ans << endl;
	return 0;
}
```

## 差分

------

**任务：**

给定一个长度为 $n$ 的数列 ${a_1,a_2,\cdots,a_n}$，每次可以选择一个区间$[l,r]$，使这个区间内的数都加 $1$ 或者都减 $1$。问至少需要多少次操作才能使数列中的所有数都一样，并求出在保证最少次数的前提下，最终得到的数列有多少种。

**分析：**

差分的思想是记录原数组 $a$ 相邻元素的差，公式就是$s[i]=a[i]-a[i-1]$

对于区间操作可以大幅加速时间，如果要对原数组的$[l,r]$区间$+k$，可以修改$s[l]+=k$，$s[r+1]-=k$，再对差分数组 $s$ 做一遍前缀和，就可以得到区间操作后的原数组，把遍历的$O(n)$降到$O(1)$

对于这个任务，先将其做差分，然后所有正偏差、负偏差求和再取绝对值，设分别为$pos$，$neg$，易得：
$$
最少操作次数=min(pos, neg) + abs(pos - neg)
$$

$$
数列种类=1 + abs(pos - neg)
$$

**代码：**

>   例题：洛谷P4552 [Poetize6] IncDec Sequence
>
>   https://www.luogu.com.cn/problem/P4552

```cpp
#include <iostream>
#include <cmath>
using namespace std;

const int MAX = 1e5 + 5;
int a[MAX], s[MAX];
int N;
long long pos, neg;

int main() {
    cin >> N;
    for (int i = 1; i <= N; ++i) cin >> a[i];
    for (int i = 1; i <= N; ++i) s[i] = a[i] - a[i - 1];
    for (int i = 2; i <= N; ++i) {
        if (s[i] > 0) pos += s[i];
        else neg += -s[i];
    }
    cout << min(pos, neg) + abs(pos - neg) << endl;
    cout << 1 + abs(pos - neg) << endl;

    return 0;
}
```

## 单调队列

------

**任务：**

有一个长为 $n$ 的序列 $f$，以及一个大小为 $k$ 的窗口。现在这个从左边开始向右滑动，每次滑动一个单位，求出每次滑动后窗口中的最大值和最小值。

**分析：**

朴素的想法是每滑动一次就遍历一遍窗口中的所有元素，但这太慢了

考虑维护一个双向队列，它是单调的，最大的在前面，从前到后变小，目标是处理窗口中的最大值

在滑动后，需要处理一个新的值，位置为 $x$，需要把 $f[x]$ 放到队列尾

因为目标是窗口中的最大值，所以位置在 $x$ 之前且比 $f[x]$ 小的数都可以舍弃

更新后，队列最前端的数可能已经不在窗口内，检查并去除

这样，因为队列单调，则最前面的就是窗口内的最大值

**核心代码：**

> 例题：洛谷P1886 滑动窗口 /【模板】单调队列
>
> https://www.luogu.com.cn/problem/P1886

```cpp
deque<pair<int, int>> maxx;	//保存值和位置
int f[MAX];					//序列f

void process_max(int x) {//处理位置为x的数
	while (!maxx.empty() && maxx.back().first < f[x])maxx.pop_back();//之前且比f[x]小的数都可以舍弃
	maxx.push_back(make_pair(f[x], x));//把 f[x] 放到队列尾
	while (!maxx.empty() && maxx.front().second <= x - K)maxx.pop_front();//队列最前端的数可能已经不在窗口内
}
```

## 并查集

------

**任务：**

有一群人，有些人互相为亲戚，亲戚的亲戚也是亲戚，现在指定两个人，问他们是否是亲戚，要求预处理时间 $O(n)$ ，查询时间 $O(1)$

**分析：**

换句话讲，在一个图中，查询两点是否联通，要求预处理时间 $O(n)$ ，查询时间 $O(1)$

以亲戚为例，假设每个家族都有一个族长，象征这个家族，数组 $fa[i]$ 代表 $i$ 的长辈（爸爸或爷爷或...或族长）

首先假设每个人都是族长

然后考虑一对父亲和儿子，那么父亲的长辈肯定是儿子的长辈

怎么找到族长？找爸爸的爸爸的爸爸......一直到族长，查询时压缩路径使时间逼近 $O(1)$

族长相同，肯定是亲戚

**代码：**

>   例题：洛谷P1551 亲戚
>
>   https://www.luogu.com.cn/problem/P1551

```cpp
#include<iostream>
using namespace std;

int N, M, P;
int fa[5003];
int S, F;

int getfa(int n) {
    if(fa[n] == n) return n;//找到族长
    return fa[n] = getfa(fa[n]);//找爸爸的爸爸，压缩路径
}

void setfa(int son, int father) {
    fa[getfa(son)] = getfa(father);//父亲的长辈是儿子的长辈
}

int main() {
    cin >> N >> M >> P;
    for (int i = 1; i <= N; ++i) fa[i] = i;//假设每个人都是族长
    for (int i = 0; i < M; ++i) {
        cin >> S >> F;
        setfa(S, F);
    }
    for (int i = 0; i < P; ++i) {
        cin >> S >> F;
        if (getfa(S) == getfa(F)) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}
```

**进阶**

并查集并不支持删点操作，我们可以把每个查询都存下来，反过来往里面添加点。[2021 RoboCom 世界机器人开发者大赛T4](https://blog.csdn.net/zzq1775840762/article/details/120941978)

## 异或

------

**基础：**

`^`的异或指的是二进制中，对应的对应二进制位相同时异或为零，相异时异或为一

- 规律一：大小相同的数字异或结果一定为0，而0与任何数字进行异或大小不会改变。比如3 ^ 3=0, 3 ^ 0=3
- 规律二：自反性。A^B^B=A
- 规律三：二进制的异或运算符合结合律和交换律

**任务：**

**非空** 整数数组 `nums` ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。实现线性时间复杂度，只使用常量额外空间的算法。

**代码：**

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
		int ans = nums[0];
         for (int i = 1; i < nums.size(); i++)ans = ans ^ nums[i];
         return ans;
    }
};
```

> 出处：力扣[136. 只出现一次的数字](https://leetcode.cn/problems/single-number/)

## 线段树

------

**任务：**

对一个数列的两种操作：

1. 将某区间每一个数加上 $k$，要求$O(log\, n)$时间复杂度
2. 求出某区间的加和，要求$O(1)$时间复杂度（接近）

> 例题：洛谷P3372 【模板】线段树 1
>
> https://www.luogu.com.cn/problem/P3372

## 回溯

**任务：**

给你一个 **无重复元素** 的整数数组 `candidates` 和一个目标整数 `target` ，找出 `candidates` 中可以使数字和为目标数 `target` 的 所有 **不同组合** ，并以列表形式返回。你可以按 **任意顺序** 返回这些组合。

`candidates` 中的 **同一个** 数字可以 **无限制重复被选取** 。如果至少一个数字的被选数量不同，则两种组合是不同的。

```cpp
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int> > res;
        vector<int> path;
        dfs(candidates, 0, target, path, res);
        return res;
    }

    void dfs(vector<int>& candidates, int begin, int target, vector<int>& path, vector<vector<int> >& res){
        if(target == 0){
            res.push_back(path);
            return;
        }
        for(int i = begin; i < candidates.size(); i++){
            if(target - candidates[i] < 0){
                continue;
            }
            path.push_back(candidates[i]);
            dfs(candidates, i, target - candidates[i], path, res);
            path.pop_back();
        }
    }
};
```

> 出处：力扣39https://leetcode.cn/problems/combination-sum/

## 杂题思想

[按照权重的概率取随机采样](https://leetcode.cn/problems/random-pick-with-weight/submissions/553637346/)：现在有包含很多个样本数据的数组，现在对这些数进行多次有放回采样，但每个数都有自己的采样概率，这个概率存在另外一个数组里面，总概率是1，问怎么实现这个采样过程。思路是：设数组 *w* 的权重之和为 *total*。根据题目的要求，我们可以看成将 [1,*total*] 范围内的所有整数分成 *n* 个部分。给出一个随机数，看落在哪个部分，优化考虑前缀和 + 二分查找。

一个文件有9998个数，对应[1-10000]的范围，少了两个数。内存1k，怎么查找？先用公式n(n+1)/2算出1-10000的总和 ， 用公式n(n+1)(2n+1)/6算出1-10000的平方和，然后扫描那9998个数，每扫到一个就从平方和中减去这个数的平方，扫描一个就从总和中减去这个数。 知道两个数的和和平方和，解方程组即可得出这两个数

求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。递归。

统计一个文本中的出现次数最多的k个单词(code)；从数据流中找出最大的k个数：HashMap（对应第一个任务）+ 维护一个只含有k个元素的优先队列。

