# 走向竞赛

## 思维

### 反向思维

- 狄杰斯特拉寻找一对多的最短路，如何寻找多对一的最短路？把图反过来！
- 并查集并不支持删点操作，我们可以把每个查询都存下来，反过来往里面添加点。

## 字符串

### KMP匹配

------

**任务：**

给定一个字符串(长度为 $n$ )和一个模式串(长度为 $m$ )，找出模式串在字符串中出现的位置，要求时间复杂度接近 $O(n+m)$

**分析：**

朴素的想法是字符串从前往后每个位置去匹配模式串，这样的时间复杂度为$O(n*m)$

当中很多时候匹配失败，这些信息不应该被简单忽略，KMP尝试利用失败的匹配步骤

比如字符串匹配到位置 10 不再匹配，其实意味着位置 9 和之前的字符都匹配

如果模式串后面 3 个和最前面 3 个又相同，由相等传递，模式串的最前面 3 个和字符串最后面 3 个匹配

已经匹配的部分不用重新检查，直接向后继续匹配，这样减少了很多步骤

那么对于模式串每个位置，怎么快速找到与最前面一段相同的长度？

用 $kmp$ 数组表示每个位置对应的长度，在处理位置 $5$ 时，位置 $4$ 已经处理好了（找到了与最前面一段相同的长度），那么从位置 $4$ 指示的长度+1找起，若相同则 $kmp[5]=kmp[4]+1$ 

如果不等，就从位置 $4$ 指示的最前面一段子串找起，$kmp[5]=kmp[kmp[4]-1]+1$ ，一直到找到或为 0 

> 例子：
>
> ```
> 	0 1 2 3 4 5 6
> B = a b a b a c b
> P = 0 0 1 2 3 ?
> ```
>
> 位置 $4$ 指示的最前面一段子串是`a b a`

**核心代码：**

```cpp
int kmp[MAX];

void pre_kmp(string P) {
	kmp[0] = 0;
	for (int i = 1; i < P.size(); ++i) {
		int k = kmp[i - 1];
		while (k > 0 && P[i] != P[k]) k = kmp[k - 1]; //如果不等，从子串找起
		if (P[i] == P[k]) kmp[i] = k + 1;
		else kmp[i] = 0;
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

## 动态规划

动态规划（dp），说是算法，更是一种思想

核心思想：**从简单小问题开始逐渐解决复杂问题**

在这个思想下，有很多具体算法：01背包，完全背包，区间dp，等等

具体做三件事：定义状态，初始化，状态转移方程

### 01背包

------

**任务：**

你入室盗窃，面对许多东西。每个东西有重量$w$和价值$v$，你背包容量有限，怎么选择使偷走东西的总价值最大？

**分析：**

面对每个物品，都要选择拿或不拿，所以叫做**01背包**

定义状态：设 $f[i][j]$ 为考虑前 $i$ 个物品，背包容量为 $j$ 时的最大价值

初始化：不需要

状态转移方程：$f[i][j] = max(f[i-1][j], v[i]+f[i-1][j-w[i]])$

解释：要么不选第$i$个东西，要么选，选了之后背包容量为$j-w[i]$

**代码：**

> 例题：洛谷P1048 [NOIP2005 普及组] 采药
>
> https://www.luogu.com.cn/problem/P1048

```cpp
#include<iostream>
#include<cmath>
using namespace std;

int T, M;
int f[102][1003];
int v[102], t[102];

int main() {
    cin >> T >> M;
    for(int i = 1; i <= M; ++i) cin >> t[i] >> v[i];
    for(int i = 1; i <= M; ++i){
        for(int j = 1; j <= T; ++j){
            if(t[i] > j) f[i][j] = f[i-1][j];
            else f[i][j] = max(f[i-1][j], v[i]+f[i-1][j-t[i]]);
        }
  	}
    cout << f[M][T] << endl;
    return 0;
}
```

**优化：**

$f[i][j]$是二维数组，而每次循环只需要上一次数据，考虑降维（空间节约，时间仍要两层循环）

定义状态：设 $f[j]$ 为背包容量为 $j$ 时的最大价值

初始化：不需要

状态转移方程：$f[j] = max(f[j], v[i]+f[j-w[i]])$

注意从后往前循环，这样用到$f[j-w[i]]$是上一次的结果

**优化代码：**

```cpp
for(int i = 1; i <= M; ++i) 
  for(int j = T; j >= t[i]; --j) 
  	f[j] = max(f[j], v[i]+f[j-t[i]]);
```

### 二维01背包

------

**任务：**

你有一些任务，每个任务 $p$ 都要花费一些时间 $t$ 和钱 $m$ ，你的时间和钱有限，怎样分配使完成的任务最多？

**分析：**

与01背包相比，只是多了一个约束条件，所以叫**二维01背包**

三层循环：遍历任务，遍历钱，遍历时间。空间上可以滚动掉一维

定义状态：设 $f[i][j]$ 为总金钱为 $i$，总时间为 $j$ 时的最多任务

初始化：不需要

状态转移方程：$f[i][j] = max(f[i][j], f[i - m[p]][j - t[p]] + 1)$

**代码：**

> 例题：洛谷P1855 榨取kkksc03
>
> https://www.luogu.com.cn/problem/P1855

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int f[205][205];
int N, M, T;
int m[205], t[205];

int main(){
    cin >> N >> M >> T;
    for(int i = 0; i < N; ++i) cin >> m[i] >> t[i];
    for(int p = 0; p < N; ++p)
        for(int i = M; i >= m[p]; --i)
            for(int j = T; j >= t[p]; --j)
                f[i][j] = max(f[i][j], f[i - m[p]][j - t[p]] + 1);
    cout << f[M][T] << endl;
    return 0;
}
```

### 完全背包

------

**任务：**

你进入仓库盗窃，面对许多**种**东西。每**种**东西有重量$w$和价值$v$，你背包容量有限，怎么选择使偷走东西的总价值最大？（假设每种东西都有无穷多件）

**分析：**

设$ f_{i,j}$表示前 $i$ **种**物品使用 $j$ 背包容量能获得的最大价值，状态转移方程：
$$
f_{i,j}=\max\limits_{k=0}^{k\le \frac{j}{w_i}} (f_{i-1,j-k\times w_i}+k\times v_i)
$$
思想为：01背包只考虑拿一件，完全背包需要考虑所有可能的件数。

**优化：**

换一种思路：
$$
f_{i,j}=\max(f_{i-1,j},f_{i,j-w_i}+v_i)
$$
思想为：

-   要么不拿，则$f_{i,j}=f_{i-1,j}$
-   要么拿一件试试，则$f_{i,j}=f_{i,j-w_i}+v_i$，注意这里用到的是本层物品遍历的状态。

在空间上也可以滚动掉一维，但时间仍要两层遍历，外层物品遍历，内层背包容量遍历，注意背包容量从前向后遍历。

**优化代码：**

```cpp
for(int i=1;i<=N;i++)
	for(int j=w[i];j<=M;j++)
		f[j]=max(f[j],f[j-w[i]]+v[i]);
```

可以看到它和01背包的代码是很像的，**完全背包和 01 背包的区别就在于对背包容量遍历的顺序不同。**

>   练练手？洛谷P1616 疯狂的采药
>
>   https://www.luogu.com.cn/problem/P1616

### 最长上升子序列（LIS）

------

**任务：**

给定$n$个整数$A_1, A_2 \dots A_n$，从左到右按顺序选出尽量多的数，组成一个上升子序列，求长度。

**分析：**

考虑动态规划，定义状态$dp_i$为以$A_i$结尾的最长上升子序列长度，则状态转移方程为：
$$
dp_i=max\{0,dp_j|j<i,A_j<A_i\} + 1
$$
最终答案为$ max\{dp_i\} $，总的时间复杂度为$O(n^2)$

>   练练手？洛谷P1020 [NOIP1999 普及组] 导弹拦截
>
>   https://www.luogu.com.cn/problem/P1020
>
>   补充： $\text{Dilworth}$定理——将一个序列剖成若干个单调不升子序列的最小个数等于该序列最长上升子序列的个数

### 找钱

------

**任务：**

你有$N$种不同的面额的纸币$m_1,m_2,\dots m_N$，要组合成$M$元，求有几种组合方法。

**分析：**

考虑动态规划，定义状态$dp[i][j]$是使用前$i$种纸币拼成$j$元的组合方法数，则状态转移方程为：
$$
dp[i][j] = \sum_{k=0}^{\lfloor \frac{j}{m_i} \rfloor} dp[i-1][j-k\times m_i]
$$
最终答案为$dp[N][M]$。

两层循环：遍历面额，遍历钱。在加上$k$从$0$循环到$\lfloor \frac{j}{m_i} \rfloor$。

初始化：令所有$dp[i][0]=1$。

**代码：**

```cpp
#include<iostream>
using namespace std;

int N, M;
const int MAXN = 1e3+5;
const int MAXM = 1e4+5;
int ms[MAXN];
int dp[MAXN][MAXM];

int main(){
    cin >>N>>M;
    for(int i=1;i<=N;++i)cin>>ms[i];
    for(int i=0;i<=N;++i)dp[i][0]=1;
    for(int i=1;i<=N;++i){
        for(int j=1;j<=M;++j){
            int K = j / ms[i];
            for(int k=0;k<=K;++k){
                dp[i][j]+=dp[i-1][j-k*ms[i]];
            }
        }
    }
    cout << dp[N][M] << endl;
    return 0;
}
```

**优化：**

考虑在状态转移方程中，在面额循环中，只用到了上层面额的值，考虑空间上滚动掉一维。

优化状态转移方程，思想与完全背包相似：
$$
dp[i][j]=dp[i-1][j]+dp[i][j-m_i]
$$

```cpp
dp[0] = 1;
for(int i=1;i<=N;++i){
    for(int j=ms[i];j<=M;++j){
        dp[j]+=dp[j-ms[i]];               
    }
}
```

### 乘积最大子数组

核心思想：如果当前位置的最优解未必是由前一个位置的最优解转移得到的，要**进行分类讨论**。

**任务：**

一个整数数组 `nums` ，找出数组中乘积最大的非空连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

**分析：**

如果我们用 $f_{\max}(i)$ 来表示以第 i 个元素结尾的乘积最大子数组的乘积，第一次考虑我们会想：
$$
f_{\max}(i) = \max_{i = 1}^{n} \{ f(i - 1) \times a_i, a_i \}
$$
但这是错误的，当前位置的最优解未必是由前一个位置的最优解转移得到的。所以**我们可以根据正负性进行分类讨论。**

考虑当前位置如果是一个负数的话，那么我们希望以它前一个位置结尾的某个段的积也是个负数，这样就可以负负得正，并且我们希望这个积尽可能「负得更多」，即尽可能小。如果当前位置是一个正数的话，我们更希望以它前一个位置结尾的某个段的积也是个正数，并且希望它尽可能地大。因此我们维护两个数组：
$$
    \begin{aligned}
        f_{\max}(i) &= \max_{i = 1}^{n} \{ f_{\max}(i - 1) \times a_i, f_{\min}(i - 1) \times a_i, a_i \} \\
        f_{\min}(i) &= \min_{i = 1}^{n} \{ f_{\max}(i - 1) \times a_i, f_{\min}(i - 1) \times a_i, a_i \}
    \end{aligned} 
$$

### 分治？

动态规划跟分治算法很相似,都是将大问题拆分成小问题逐个击破.

> 想想归并排序，一个由上到下再反过去递归的分支

分治算法的特点：

- 分治算法每次分解出来的子问题是互相独立,不互相影响的.每个子问题都是独立地被求解.
- 分治算法是自顶而下求解的

动态规划和分治算法的差别:

- 动态规划的子问题并不是互相独立,是有交集的.
- 动态规划多数都是自底而上来求解问题的,先解决小问题,再由小问题解决大问题.(即由之前存在过的状态推导出后面的状态)
- 动态规划会将解决过的子问题的结果记忆起来,用于求解更大的问题或者,遇到相同的子问题时不用再次计算,直接在使用记忆的结果即可.

## 优化方法

### 重新思考排序

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

### 二分

------

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

> 看到最大的最小（最小的最大），可能时二分或者二分答案

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

### 二维前缀和

------

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

### 差分

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

### 单调队列

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

### 并查集

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

### 异或

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

### 线段树

------

**任务：**

对一个数列的两种操作：

1. 将某区间每一个数加上 $k$，要求$O(log\, n)$时间复杂度
2. 求出某区间的加和，要求$O(1)$时间复杂度（接近）

底层存储？

改什么？

适合什么？

总体思路？

**代码：**

> 例题：洛谷P3372 【模板】线段树 1
>
> https://www.luogu.com.cn/problem/P3372

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const int MAX = 1e5 + 5;
ll N, M;
ll nums[MAX], tree[MAX * 4], tag[MAX * 4];

void push_up(ll p) {///
	tree[p] = tree[2 * p] + tree[2 * p + 1];
}

void upd_node(ll p, ll l, ll r, ll t) {///
	tag[p] += t;
	tree[p] += t * (r - l + 1);
}

void push_down(ll p, ll l, ll r) {
	if (!tag[p])return;
	ll mid = (l + r) / 2;
	upd_node(2 * p, l, mid, tag[p]);
	upd_node(2 * p + 1, mid + 1, r, tag[p]);
	tag[p] = 0;
}

void build(ll p, ll l, ll r) {//以p为当前节点，当前节点包含l~r，建树
	tag[p] = 0;
	if (l == r) { tree[p] = nums[l]; return; }//叶子
	ll mid = (l + r) / 2;
	build(2 * p, l, mid);
	build(2 * p + 1, mid + 1, r);
	push_up(p);//整合子节点的信息
}

//以p为当前节点，当前节点包含l~r，以nl~nr为目标节点，更新每个加k
void update(ll nl, ll nr, ll l, ll r, ll p, ll k) {
	if (nl <= l && r <= nr) {//p的范围被包含在目标中
		upd_node(p, l, r, k);//更新节点与懒标记
		return;
	}
	push_down(p, l, r);//向下传递信息
	ll mid = (l + r) / 2;
	if (nl <= mid)update(nl, nr, l, mid, 2 * p, k);//递归向下处理
	if (nr > mid) update(nl, nr, mid + 1, r, 2 * p + 1, k);
	push_up(p);//整合子节点的信息
}

//以p为当前节点，当前节点包含l~r，以nl~nr为目标节点，查询加和
ll query(ll nl, ll nr, ll l, ll r, ll p) {
	ll ans = 0;
	if (nl <= l && r <= nr)return tree[p];//已被包含，直接返回
	ll mid = (l + r) / 2;
	push_down(p, l, r);//防止未更新
	if (nl <= mid)ans += query(nl, nr, l, mid, p * 2);//递归求和
	if (nr > mid) ans += query(nl, nr, mid + 1, r, p * 2 + 1);
	return ans;
}

int main() {
	scanf("%lld%lld", &N, &M);
	for (ll i = 1; i <= N; i++) scanf("%lld", &nums[i]);
	ll code, x, y, k;
	build(1, 1, N);//建树
	while (M--) {
		scanf("%lld", &code);
		if (code == 1) {
			scanf("%lld%lld%lld", &x, &y, &k);
			update(x, y, 1, N, 1, k);//将区间[x, y]内每个数加上k
		} else {
			scanf("%lld%lld", &x, &y);
			printf("%lld\n", query(x, y, 1, N, 1));//输出区间[x, y]内每个数的和
		}
	}
	return 0;
}
```

### 回溯

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

## 树

### 树的遍历

**任务：**

给出二叉树的中序和后序遍历序列，输出层序遍历序列

**代码：**

```cpp
#include<iostream>
#include<queue>
using namespace std;

struct Btree{
    int data;
    Btree *left,*right;
    Btree(int d):data(d),left(NULL),right(NULL){}
};
int N, postord[30], midord[30];

Btree* build(int post_head, int post_tail, int mid_head, int mid_tail){
    if(post_head > post_tail)return NULL;
    Btree *root = new Btree(postord[post_tail]);
    int mid_root = mid_head;
    while(midord[mid_root] != postord[post_tail]){
        mid_root++;
    }
    int left_size = mid_root - mid_head;
    root->left = build(post_head, post_head + left_size - 1, mid_head, mid_root - 1);
    root->right = build(post_head + left_size, post_tail - 1, mid_root + 1, mid_tail);
    return root;
}

void levelOrder(Btree *root){
    queue<Btree*> q;
    q.push(root);
    while(!q.empty()){
        Btree *node = q.front();
        q.pop();
        cout << node->data;
        if(node->left != NULL)q.push(node->left);
        if(node->right != NULL)q.push(node->right);
    }
}

int main(){
    cin >> N;
    for(int i = 0; i < N; i++)cin >> postord[i];
    for(int i = 0; i < N; i++)cin >> midord[i];
    Btree *root = build(0, N - 1, 0, N - 1);
    levelOrder(root);
    return 0;
}
```

### 树的直径

> 来自PAT 甲级 1021 Deepest Root

**任务：**

给出N个结点与N-1条边，问：它们能否形成一棵N个结点的树？如果能，则从中选出结点作为树根，使得整棵树的高度最大。输出所有满足要求的可以作为树根的结点。

**分析：**

判断图是否连接用并查集解决。

当图连通时，由于题目保证只有N-1条边，因此一定能确定是一棵树，下面的任务就是选择合适的根结点，使得树的高度最大。具体做法为：

1. 先任意选择一个结点，从该结点开始遍历整棵树，获取能达到的最深的顶点(记为结点集合A)；
2. 然后从集合A中任意一个结点出发遍历整棵树，获取能达到的最深的顶点(记为结点集合B)。
3. 这样集合A与集合B的并集即为所求的使树高最大的根结点。

因此，这道题最快只用两次DFS就够了，比较笨的方法是找到每个叶节点然后dfs求最长路并记录，最后将所有最长路为最大值的节点输出，在PAT上也能过，但是在牛客网上是过不了的（牛客网数据略强）。

证明过程见[链接](https://www.cnblogs.com/fxh0707/p/14327987.html)

### 二叉搜索树

```cpp
class Node{
public:
    int data;
    Node* left, *right;
    Node(int data){
        this->data = data;
        left = right = NULL;
    }
};
Node *tree = NULL;

Node *build(Node *root, int data){
    if(root == NULL) return new Node(data);
    if(data < root->data) root->left = build(root->left, data);
    else root->right = build(root->right, data);
    return root;
}
```

> 练练手：**1043 Is It a Binary Search Tree**

### 最近公共祖先 LCA

------

**任务：**

给定一棵有根多叉树，请求出指定两个点直接最近的公共祖先

**代码：**

> 例题：洛谷P3379 【模板】最近公共祖先（LCA）
>
> https://www.luogu.com.cn/problem/P3379

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int N, M, S;
const int MAX = 5e5+10;
int depth[MAX], fa[MAX][22], lg[MAX];
//fa[i][j] = i 的 2^j 个父亲
//lg[i] = log(2, i) + 1

struct node {
    int t, nex;
}tree[MAX << 1];//链式前向星
int head[MAX], tot;

void add(int x, int y) {
    tree[++tot].t = y;
    tree[tot].nex = head[x];
    head[x] = tot;
}

//初始化，处理父亲
void dfs(int now, int father) {
    fa[now][0] = father;
    depth[now] = depth[father] + 1;
    for(int i = 1; i <= lg[depth[now]]; ++i) fa[now][i] = fa[fa[now][i-1]][i-1];
    //i 的 2^i 个父亲 = i 的 2^(i-1) 个父亲的 2^(i-1) 个父亲
    for(int i = head[now]; i != 0; i = tree[i].nex)
        if(tree[i].t != father) dfs(tree[i].t, now);
}

int LCA(int x, int y) {
    if(depth[x] < depth[y]) swap(x, y);//确保x比y深
    while(depth[x] > depth[y]) x = fa[x][lg[depth[x]-depth[y]] - 1];
    //现在x与y同一深度
    if(x == y) return x; //以防x是y的根
    for(int k = lg[depth[x]] - 1; k >= 0; --k){
        //先检查较远的父亲，再检查较近的父亲，如果不是同一个父亲就更新
        if(fa[x][k] != fa[y][k]){
            x = fa[x][k];
            y = fa[y][k];
        }
    }
    return fa[x][0];
}

int main() {
    cin >> N >> M >> S;//N,M,S分别表示树的结点个数、询问的个数和树根结点的序号
    for(int i = 1; i <= N - 1; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    for(int i = 1; i <= N; ++i) lg[i] = lg[i-1] + (1 << lg[i-1] == i);//处理log
    dfs(S, 0);
    for(int i = 1; i <= M; ++i) {
        int x, y;
        scanf("%d%d",&x, &y);
        printf("%d\n", LCA(x, y));
    }
    return 0;
}
```

### Trie前缀树

Trie（发音类似 "try"）或者说 **前缀树** 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补完和拼写检查。

```cpp
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Trie {

private:
    bool isEnd;
    vector<Trie*> children;

    Trie* searchPrefix(string prefix) {
        Trie* node = this;  // 从字典树的根开始，搜索前缀。
        for (char c : prefix) {
            c -= 'a';
            if (node->children[c] == nullptr) {
                // 如果没有找到前缀中的任何字符，就立即返回。
                return nullptr;
            }
            // 如果找到前缀中的字符，则继续向下搜索。
            node = node->children[c];
        }
        // 返回前缀中的最后一个节点。
        return node;
    }

public:
    Trie() {
        isEnd = false;
        children = vector<Trie*>(26, nullptr);
    }
    
    void insert(string word) {
        Trie* node = this;  // 从字典树的根开始，插入字符串。
        for (char c : word) {
            if (node->children[c - 'a'] == nullptr) {
                // 子节点不存在。创建一个新的子节点，
                // 然后沿着指针移动到子节点，继续搜索下一个字符。
                node->children[c - 'a'] = new Trie();
            }
            // 子节点存在。沿着指针移动到子节点，继续处理下一个字符。
            node = node->children[c - 'a'];
        }
        // 字符串的最后一个字符，然后将当前节点标记为字符串的结尾。
        node->isEnd = true;
    }
    
    bool search(string word) {
        Trie* node = this->searchPrefix(word);
        return node != nullptr && node->isEnd;
    }
    
    bool startsWith(string prefix) {
        return this->searchPrefix(prefix) != nullptr;
    }
};

int main(){
    Trie* trie = new Trie();
    trie->insert("apple");
    cout << trie->search("apple") << endl;   // 返回 true
    cout << trie->search("app") << endl;     // 返回 false
    cout << trie->startsWith("app") << endl; // 返回 true
    trie->insert("app");
    cout << trie->search("app") << endl;     // 返回 true
    return 0;
}
```

## 图论

### 邻接矩阵

------

一种存图方式，适合密集图，因为简单所以适合其他操作（比如翻转图）

```cpp
int mmp[MAX][MAX];
memset(mmp, 127, sizeof(mmp));//赋值无穷大
```

**遍历起点为 $n$ 的所有终点：**

```cpp
for (int i = 1; i < MAX; ++i) cout << mmp[n][i] << " ";
```

**添加一条从 $x$ 到 $y$ 的边：**

```cpp
mmp[x][y] = w;//w 为边权
```

### 朴素存图

非常朴素的存图方式

```cpp
vector<int> mmp[MAX];//MAX 为最大节点数
```

**遍历起点为 $n$ 的所有终点：**

```cpp
for (int to : mmp[n]) cout << to << " ";
```

**添加一条从 $x$ 到 $y$ 的边：**

```cpp
mmp[x].pushback(y);
```

### 链式前向星

链式前向星是一种高效的存图方式

```cpp
struct Edge{
    int to,nxt;
}edge[MAX << 1];//因为存边，所以大小是2倍最大节点数
int head[MAX];	//MAX 为最大节点数
int cnt;		//cnt 为一共有多少条边
```

$head[i]$ 表示节点 $i$ 为起点的第一条边在 $edge$ 数组中的索引

$edge[j]$ 表示终点为 $to$ 的一条边，要找的下一条边在 $edge$ 数组中的索引为 $nxt$ ，$j$ 只是索引没有具体意义

所以，比如要找起点为 $2$ 的边和终点，先从 $head[2]$ 找到第一条边的索引，再到 $edge$ 数组中寻找具体信息， 通过 $nxt$ 找到下一条边，当 $nxt==0$ 时，表示找完了

**遍历起点为 $n$ 的所有终点：**

```cpp
for(int i = head[n]; i; i = edge[i].nxt){
	cout << edge[i].to << " ";
}
```

**添加一条从 $x$ 到 $y$ 的边：**

```cpp
void add(int x,int y){
    edge[++cnt].to = y;
    edge[cnt].nxt = head[x];
    head[x] = cnt;
}
```

**如果要存边权：**

```cpp
struct Edge{
    int to,nxt,w;
}edge[MAX << 1];
int head[MAX];
int cnt;

void add(int x,int y, int w){
    edge[++cnt].to = y;
    edge[cnt].nxt = head[x];
    edge[cnt].w = w;
    head[x] = cnt;
}
```

### 弗洛伊德最短路

------

**任务：**

给定一个 $n$ 个点的加权图，求任意起点到任意终点的最短距离，要求时间复杂度$O(n^3)$

**分析：**

考虑从起点 $i$ 到 终点 $j$ 的最短路

对于每一个可能的中转点 $k$ ，考虑先从 $i$ 到 $k$ ，再从 $k$ 到 $j$ 的距离

注意，代码中 $k$ 在最外面一层，是以中转点为驱动的查找

**核心代码：**

```cpp
int mmp[MAX][MAX];//邻接矩阵存图，MAX 为最大节点数

void init(){
    //初始化，假设 i 到 j 的距离无穷大，注意不要溢出
    for(int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) mmp[i][j] = 1e9;
    for(int i = 0; i < N; ++i) mmp[i][i] = 0;//到自己的距离为0
}

void floyd(){
    for(int k = 0; k < N; ++k)//N 为节点数
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                mmp[i][j] = min(mmp[i][j], mmp[i][k] + mmp[k][j]);
}
```

>   练练手？洛谷P1119 灾后重建
>
>   https://www.luogu.com.cn/problem/P1119

### 最小环

**任务：**

给定一张无向图，求图中一个至少包含 3 个点的环，环上的节点不重复，并且环上的边的长度之和最小。该问题称为无向图的最小环问题。在本题中，你需要输出最小的环的边权和。若无解，输出 `No solution.`

**分析：**

基于最短路径继续构造，已知 $i \to ... \to j$ 的最短路径，再加上一步 $i \to ... \to j \to i$ 即为最小环。

问题在于无法保证这样的环至少包含 3 个点，可能出现 $i \to j \to i$

那么尝试构造 $i \to ... \to j \to k \to i$

问题在于无法保证 k 结点之前没用到，可能出现 $i \to k \to j \to k \to i $

联想到弗洛伊德最短路的一个很好的性质，在枚举 $k_i$ 的时候，之前得到的最短路径不包括 k 点。

那么我们便可以从这前 k-1 个点中选出 $i \to ... \to j$，且这个路径不包含 **k** 点，连接 $i \to ... \to j \to k \to i$ ，我们就得到了一个经过 **i , j , k** 的最小环。

**代码：**

```cpp
#include<iostream>
#include<cmath>
using namespace std;

int N,M;
const long long inf = 1e13;
long long dis[105][105]; // dis[i][j]表示从起点到(i,j)的最短路
long long mmp[105][105]; // mmp[i][j]表示(i,j)的权值
long long u,v,w;
long long ans = inf;

int main() {
    cin >> N >> M;

    for(int i=1;i<=N;++i){
        for(int j=1;j<=N;++j){
            if(i==j) dis[i][j] = 0;
            else{
                dis[i][j] = inf;
                mmp[i][j] = inf;
            }
            
        }
    }

    for(int i=1;i<=M;++i){
        cin >> u >> v >> w;
        mmp[u][v] = min(mmp[u][v],w);
        mmp[v][u] = mmp[u][v];
        dis[u][v] = min(dis[u][v],w);
        dis[v][u] = dis[u][v];
    }

    for(int k=1;k<=N;++k){
        for(int i=1;i<k;++i){
            for(int j=i+1;j<k;++j){
                ans = min(ans,dis[i][j]+mmp[j][k]+mmp[k][i]);
            }
        }

        for(int i=1;i<=N;++i){
            for(int j=1;j<=N;++j){
                dis[i][j] = min(dis[i][j],dis[i][k]+dis[k][j]);
                dis[j][i] = dis[i][j];
            }
        }
    }

    if(ans==inf) cout << "No solution." << endl;
    else cout << ans << endl;
    return 0;
}
```

> 例题1：洛谷P6175 无向图的最小环问题
>
> https://www.luogu.com.cn/problem/P6175
>
> 当条件特殊一点，可以试着用并查集维护环。例题2：P2661 [NOIP2015 提高组] 信息传递
>
> https://www.luogu.com.cn/problem/P2661

### 狄杰斯特拉最短路

------

**任务：**

给定一个 $n$ 个点，$m$ 条有向边的带非负权图，求从 $s$ 出发，到每个点的最短距离，要求时间复杂度$O(nlog\, n)$

**分析：**

首先从起点考虑，有很多直达节点，找到距离最短的节点 $x$

那么，到节点 $x$ 的最短距离，就确定了（没有更短的边了）

那么，更新起点为 $x$ 的直达节点，它们到起点的距离更新为： $x$ 的距离加 $x$ 到节点的距离

现在，从起点考虑，有很多直达节点（加入刚刚跟新的），找到距离最短的节点 $y$ ......

不断循环，直到节点被考虑完。因为总是找最短距离，并且要维护，所以使用优先队列

**核心代码：**

```cpp
class node {
public:
    node(int pos, ll d): position(pos), dis(d){}
    int position;
    ll dis;
    bool operator<(const node& nd) const {
        return dis > nd.dis;
    }//在优先队列排序用
};

ll dis[MAX];//MAX 为最大节点数，dis 为要求的最短距
priority_queue<node> Q;

void dijkstra() {
    for (int i = 1;i <= N;i++) dis[i] = 2e9;//先假设距离无穷大
    dis[S] = 0;//S为起点
    Q.push(node(S, 0));
    while (!Q.empty()) {
        node top = Q.top();
        Q.pop();
        int pos = top.position;
        if (top.dis != dis[pos]) continue;
        //如果将要处理的点已经在其他方向处理过了，距离不符要跳过
        for (int i = head[pos]; i; i = edges[i].next) {//链式前向星存图
            int to = edges[i].to;
            ll w = edges[i].weight;
            if (dis[pos] + w < dis[to]) {
                dis[to] = dis[pos] + w;
                Q.push(node(to, dis[to]));
            }
        }
    }
}
```

>   练练手？洛谷P4779 【模板】单源最短路径（标准版）
>
>   https://www.luogu.com.cn/problem/P4779

*补充：狄杰斯特拉寻找一对多的最短路，如何寻找多对一的最短路？把图反过来！*

另外一个版本：

```cpp
#define INF 1e9
struct node {
	int dis, id;
	bool operator<(const node& a) const { return dis > a.dis; }
	node(int d, int x) { dis = d, id = x; }
};
int vis[5005], dis[5005];

void dijkstra(int s) {
	priority_queue<node> q;
	for (int i = 1; i <= N; i++) dis[i] = INF;
	memset(vis, 0, sizeof(vis));
	dis[s] = 0;
	q.push(node(0, s));
	while (!q.empty()) {	
		int u = q.top().id;
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = head[u]; i; i = e[i].next) {
			int v = e[i].v;
			if (dis[v] > dis[u] + e[i].w) {
				dis[v] = dis[u] + e[i].w;
				if (!vis[v]) q.push(node(dis[v], v));
			}
		}
	}
	return;
}
```

**进阶1**

在图中找最短路，如果多条路径都最短，选择开销最少的。输出最短路径长，最小开销，以及路径。（PAT 甲级 **1030 Travel Plan**）

```cpp
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

int N,M,S,E;

class Edge{
    public:
    int to, nxt, dis, cost;
    Edge(int to, int nxt, int dis, int cost):to(to), nxt(nxt), dis(dis), cost(cost){}
    Edge(){}
};

Edge edges[505*505];
int head[505], edgeCnt=0;

void addEdge(int u, int v, int dis, int cost){
    edges[++edgeCnt] = Edge(v, head[u], dis, cost);
    head[u] = edgeCnt;
}

class Node{
public:
    int pos, dis, cost;
    Node(int pos, int dis, int cost):pos(pos), dis(dis), cost(cost){}
    bool operator < (const Node& n) const{  // 综合判断
        if(dis == n.dis) return cost > n.cost;
        return dis > n.dis;
    }
};

int minDis[505], minCost[505];
bool vis[505];
int pre[505];


void dijstra(int s){
    priority_queue<Node> q;
    memset(minDis, 0x3f, sizeof(minDis));
    memset(minCost, 0x3f, sizeof(minCost));
    memset(vis, 0, sizeof(vis));
    q.push(Node(s, 0, 0));
    minDis[s] = 0;
    minCost[s] = 0;
    while(!q.empty()){
        Node topNode = q.top();
        q.pop();
        int u = topNode.pos;
        if(vis[u]) continue;  // 只处理一次，可以记录路径
        vis[u] = true;
        for(int i = head[u]; i; i = edges[i].nxt){
            int v = edges[i].to;
            int d = edges[i].dis;
            int c = edges[i].cost;
            if(minDis[v] > minDis[u] + d){
                minDis[v] = minDis[u] + d;
                minCost[v] = minCost[u] + c;
                q.push(Node(v, minDis[v], minCost[v]));
                pre[v] = u;
            }else if(minDis[v] == minDis[u] + d && minCost[v] > minCost[u] + c){
                minCost[v] = minCost[u] + c;
                q.push(Node(v, minDis[v], minCost[v]));
                pre[v] = u;
            }
        }
    }
}

void dfs(int end){ //倒着向前递归
    if(end == S){
        cout << S << " ";
        return;
    }
    dfs(pre[end]);
    cout << end << " ";  // 尾递归
}

int main(){
    cin >> N >> M >> S >> E;
    for(int i = 0; i < M; i++){
        int u,v,d,c;
        cin >> u >> v >> d >> c;
        addEdge(u, v, d, c);
        addEdge(v, u, d, c);
    }
    dijstra(S);
    dfs(E);
    cout <<  minDis[E] << " " << minCost[E] << endl;
    return 0;
}
```

**进阶2**

给定一个 $n$ 个点，$m$ 条有向边的带非负权图，每条路径有对应的距离与价值，对于每个起点$s$，计算到每个节点的最短距离，并且记录路径，如果两条路径距离相同，优先选择价值高的路径。

对于每个起点$s$，输出到每个终点的最短路径长度，价值和路径。

对于所有以$s$为起点的最短路径中，肯定存在一个最远的终点，找到目标起点$ans_s$，使得最远的终点路径长最短。如果有多个起点符合要求，则选编号最小的。

> 不是人话的版本：找到最远的最短路径最短的起点。

知识点：双关键字、记录路径。

代码：

```cpp
//7-3 打怪升级 (25 分)
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
const int MAX = 1010;

bool vis[MAX];
int N, M, MAX_LEN[MAX];
int MIN_LEN[MAX], MAX_VAL[MAX];
int a, b, l, v, pre[MAX];
int LEN[MAX][MAX], VAL[MAX][MAX];


// 以 s 为起点做一次 dijkstra
int dijkstra(int s)
{
	memset(vis, 0, sizeof vis);// 初始所有点都没有被访问过
	memset(MIN_LEN, 0x3f, sizeof MIN_LEN);// 初始到每个点的最短路径为无穷大
	memset(MAX_VAL, 0, sizeof MAX_VAL);// 初始到每个点的价值为0
	
	MIN_LEN[s] = 0;// 初始起点到自己的最短路径为0
	MAX_VAL[s] = 0;// 初始起点的价值为0

	while(true)
	{

        // 找到最小的MIN_LEN[i]，并且没有被访问过
		int t = -1;
		for(int i = 1; i <= N; i++)
			if(!vis[i] && (t == -1 || MIN_LEN[t] > MIN_LEN[i]))
				t = i;
		
		if(t == -1)
			break;// 找不到，退出
		vis[t] = true;// 这个点的最短路径已经找到，标记为已访问
		
		for(int i = 1; i <= N; i++)
		{
            // 更新到每个点的最短路径
			if(MIN_LEN[i] > MIN_LEN[t] + LEN[t][i])
			{
				pre[i] = t;// 记录前驱
				MIN_LEN[i] = MIN_LEN[t] + LEN[t][i];// 更新最短路径
				MAX_VAL[i] = MAX_VAL[t] + VAL[t][i];// 更新最大价值
			}
			else if(MIN_LEN[i] == MIN_LEN[t] + LEN[t][i]) // 如果路径长度相同，比较价值
			{
				if(MAX_VAL[i] < MAX_VAL[t] + VAL[t][i])// 如果价值更多，更新
				{
					pre[i] = t;
					MAX_VAL[i] = MAX_VAL[t] + VAL[t][i];
				}
			}
		}
	}
	
	int ms = 0;
	for(int i = 1; i <= N; i++)
		if(ms < MIN_LEN[i])
			ms = MIN_LEN[i];// 找到到所有节点的最短路径长度中最大的长度
	return ms;
}


// x 为终点，s 为起点，打印路径
void dfs(int x, int s)
{
	if(x == s) return;
	dfs(pre[x], s);
	printf("->%d", x);
}

int main()
{
	memset(LEN, 0x3f, sizeof LEN); // 初始路径长度为无穷大
	
	scanf("%d %d", &N, &M);
	while(M--)
	{
		scanf("%d %d %d %d", &a, &b, &l, &v);
		LEN[a][b] = LEN[b][a] = min(LEN[a][b], l); // 距离
		VAL[a][b] = VAL[b][a] = max(VAL[a][b], v); // 价值
	}
	
	for(int i = 1; i <= N; i++) // 遍历每个点，找到到每个点的最短路径长度中最大的长度
		MAX_LEN[i] = dijkstra(i);
	
	int ans_s = 1;
	for(int i = 1; i <= N; i++)
		if(MAX_LEN[ans_s] > MAX_LEN[i])
			ans_s = i;// 找到最小的最大值
	
	printf("%d\n", ans_s);
	dijkstra(ans_s);

	// 输出到每个点的路径，以及最短路径长度和最大价值
	for(int i = 1; i <= N; i++){
		printf("%d", ans_s);
		dfs(i, ans_s);
		printf("\n");
		printf("%d %d\n", MIN_LEN[i], MAX_VAL[i]);
	}
	return 0;
}
```

> 例题：[2021 RoboCom 世界机器人开发者大赛T3](https://blog.csdn.net/zzq1775840762/article/details/120941978)

如果要找多条最短路？

```cpp
if(vis[u] && now.dis > dis[u]){
    continue;
}
```

### SPFA 最短路

**思想：**

SPFA 算法是 Bellman-Ford算法 的队列优化算法的别称，通常用于求含负权边的单源最短路径，以及判负权环。SPFA 最坏情况下时间复杂度和朴素 Bellman-Ford 相同，为 $O(mn)$。

与狄杰斯特拉最短路思想不同，当一个节点被处理，SPFA 不保证已经找到最短路径。如果在一次处理中 v 节点的最短路径被更新，它的所有后续节点都要更新一遍，然后 v 节点的最短路径**可能**再次被更新，它的所有后续节点都要再次更新一遍……直到稳定。

**代码：**

```cpp
#include<iostream>
#include<queue>
using namespace std;

const long long INF=2147483647;
const int MAXN=10005;
const int MAXM=500005;
int N,M,S,cnt=0;
int dis[MAXN],vis[MAXN];

struct Edge{
    int next,to,dis;
}edge[MAXM]; 
int head[MAXM]; // 链式前向星

void addedge(int from,int to,int dis) { 
    edge[++cnt].next=head[from];
    edge[cnt].to=to;
    edge[cnt].dis=dis;
    head[from]=cnt;
}

void spfa(int s){
    queue<int> q; //spfa用队列
    for(int i=1; i<=N; i++) {
        dis[i]=INF; //带权图初始化
        vis[i]=0; //记录点i是否在队列中
    }
    q.push(s); dis[s]=0; vis[s]=1; //起点入队，进行标记
    while(!q.empty()){
        int u=q.front();
        q.pop(); 
        vis[u]=0; //出队标记
        for(int i=head[u]; i; i=edge[i].next) {
            int v=edge[i].to;

            if(dis[v]>dis[u]+edge[i].dis) {
                dis[v]=dis[u]+edge[i].dis;

                // 因为节点v的最短路径发生了变化，后续的节点可能也会发生变化，所以v入队再次处理
                if(vis[v]==0) {
                vis[v]=1;
                q.push(v);
                }
            }
        }
    }
}

int main() {
    cin>>N>>M>>S;
    for(int i=1; i<=M; i++) {
        int f,g,w;
        cin>>f>>g>>w; 
        addedge(f,g,w); //建图，有向图连一次边就可以了
    }
    spfa(S);
    for(int i=1; i<=N; i++)
        if(S==i) cout<<0<<" "; //如果是回到自己，直接输出0
        else cout<<dis[i]<<" "; //否则打印最短距离

    return 0;
}
```

> 练练手？洛谷P4779 【模板】单源最短路径（标准版）
>
> https://www.luogu.com.cn/problem/P4779

**进阶：**

现在思考如果存在负环会出现什么情况，负环上的节点会一次又一次地加入队列，最短距离一次又一次的缩小，永远不会停止循环。

我们可以记录每个节点的入队次数，如果某个节点的入队次数大于N，则出现负环。

**核心代码：**

```cpp
bool spfa(int s) {
  queue<int> q;
  memset(h, 63, sizeof(h));
  h[s] = 0, vis[s] = 1;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = 0;
    for (int i = head[u]; i; i = e[i].next) {
      int v = e[i].v;
      if (h[v] > h[u] + e[i].w) {
        h[v] = h[u] + e[i].w;
        if (!vis[v]) {
          vis[v] = 1;
          q.push(v);
          t[v]++; // 记录入队次数
          if (t[v] == N + 1) return false; // 如果入队次数超过N次，说明有负环
        }
      }
    }
  }
  return true;
}
```

### Johnson 全源最短路

**任务：**

给定一个包含 n 个结点和 m 条带权边的有向图，求所有点对间的最短路径长度，一条路径的长度定义为这条路径上所有边的权值和。注意：边权**可能**为负，且图中**可能**存在重边和自环。

**分析：**

先来看全源最短路的几个基本想法：

1. Floyd：时间复杂度为 $O(n^3)$，能够解决负权边，不能解决负环，而且很慢。
2. Dijkstra：以每个点为源点做一次 Dijkstra，时间复杂度为 $O(nm\log (n))$，时间上可以，但是 Dijkstra 只能解决非负权边，一旦出现负权边就得另想办法。
3. BellmanFord：以每个点为源点做一次 BellmanFord，时间复杂度为 $O(n^2m)$，能搞定所有权值情况，但是太慢。

Johnson 算法则通过一种方法来给每条边重新标注边权。

我们新建一个虚拟节点（设它的编号为 0 ）。从这个点向其他所有点连一条边权为 0 的边。

接下来用 Bellman-Ford 算法求出从 0 号点到其他所有点的最短路，记为 $h_i$ 。

假如存在一条从 u 点到 v 点，边权为 w 的边，则我们将该边的边权重新设置为 $w+h_u-h_v$

接下来以每个点为起点，跑 n 轮 Dijkstra 算法即可求出任意两点间的最短路了。

容易看出，该算法的时间复杂度是 $O(nm \log (m))$ 。

> 证明：[Studying Father's luogu blog](https://www.luogu.com.cn/blog/StudyingFather/johnson-algorithm)

**代码：**

```cpp
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

#define INF 1e9

struct edge {
	int v, w, next;
} e[10005];
int cnt, head[5005]; // 链式前向星

struct node {
	int dis, id;
	bool operator<(const node& a) const { return dis > a.dis; }
	node(int d, int x) { dis = d, id = x; }
};

int vis[5005], t[5005];
int N, M;
long long h[5005], dis[5005];

void addedge(int u, int v, int w) {
	e[++cnt].v = v;
	e[cnt].w = w;
	e[cnt].next = head[u];
	head[u] = cnt;
}

bool spfa(int s) {
	queue<int> q;
	memset(h, 63, sizeof(h));
	h[s] = 0, vis[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for (int i = head[u]; i; i = e[i].next) {
			int v = e[i].v;
			if (h[v] > h[u] + e[i].w) {
				h[v] = h[u] + e[i].w;
				if (!vis[v]) {
				vis[v] = 1;
				q.push(v);
				t[v]++; // 记录入队次数
				if (t[v] == N + 1) return false; // 如果入队次数超过N次，说明有负环
				}
			}
		}
	}
	return true;
}

void dijkstra(int s) {
	priority_queue<node> q;
	for (int i = 1; i <= N; i++) dis[i] = INF;
	memset(vis, 0, sizeof(vis));
	dis[s] = 0;
	q.push(node(0, s));
	while (!q.empty()) {
		int u = q.top().id;
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = head[u]; i; i = e[i].next) {
			int v = e[i].v;
			if (dis[v] > dis[u] + e[i].w) {
				dis[v] = dis[u] + e[i].w;
				if (!vis[v]) q.push(node(dis[v], v));
			}
		}
	}
	return;
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= M; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		addedge(u, v, w);
	}

	for (int i = 1; i <= N; i++) addedge(0, i, 0); // 虚拟点

	if (!spfa(0)) {
		cout << -1 << endl;
		return 0;
	}

	for (int u = 1; u <= N; u++)
		for (int i = head[u]; i; i = e[i].next) 
			e[i].w += h[u] - h[e[i].v];

	for (int i = 1; i <= N; i++) {
		dijkstra(i);
		long long ans = 0;
		for (int j = 1; j <= N; j++) {
			if (dis[j] == INF) ans += j * INF;
			else ans += j * (dis[j] + h[j] - h[i]);
		}
		cout << ans << endl;
	}
	return 0;
}
```

> 例题：洛谷P5905 【模板】Johnson 全源最短路
>
> https://www.luogu.com.cn/problem/P5905

### 克鲁斯卡尔最小生成树

------

**任务：**

给定一个 $n$ 个点的无向图，用树的形式连接它们（生成树），要求树的总权最小（最小生成树）

**分析：**

关于树的特点：边==节点-1，没有环

因为要求树的权最小，先把所有边排序，优先考虑权小的边

如果加上这条边出现环，则跳过，反之加上它。一直处理到边==节点-1

环可以用并查集维护

**核心代码：**

```cpp
class Edge {
public:
	Edge(int u = 0, int v = 0, int w = 0) :u(u), v(v), w(w) {}
	int u, v, w;
	bool operator<(const Edge& that) const {
		return this->w < that.w;
	}
};
Edge mmp[MAXM];

void kruskal() {
	sort(mmp, mmp + M);//先从小到大排序
	for (int i = 0; i < M; ++i) {
		if (getfa(mmp[i].u) == getfa(mmp[i].v)) continue;//树不包括环
		ans += mmp[i].w;//答案加边权
		setfa(mmp[i].v, mmp[i].u);//维护并查集
		cnt++;//边数
		if (cnt == N - 1) return;//边数==节点-1，结束
	}
}
```

> 练练手？洛谷P3366 【模板】最小生成树
>
> https://www.luogu.com.cn/problem/P3366

### 二分图

**概念与结论**

设 G=(V,E) 是一个无向图，如果顶点集合 V 可分割为两个互不相交的子集 (A,B)，并且每条边 (i,j)∈E 的两个端点 i 和 j 分别属于这两个不同的顶点子集，则称图 G 为一个二分图。

树一定是二分图。可以把本层节点归入一个集合，把父亲和儿子归入另外一个集合，对于每一层这样操作，就得到了二分图。

对于顶点数为n的二分图, 假设划分的两个集合顶点数分别为m , n-m. 显然这个二分图的最大边数为m*(n-m), 即每个顶点与对面集合所有顶点都形成的边。

**任务**

[2022 RoboCom 世界机器人开发者大赛-本科组（省赛）-- 第五题 树与二分图](https://blog.csdn.net/qq_60775983/article/details/125738638)

给定一棵树, 最多能加多少边使得它仍是二分图。

**思路**

从树的顶点开始，用dfs染一遍色，分出两个集合，最多能加多少边就是最大边数减去原来的边数。

**代码**

```cpp
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

const int MAX = 1e6+5;
vector<int> adj[MAX];
int N;
int black=0;

void dfs(int from, bool isBlack){
    if(isBlack) black++;
    for(int to: adj[from]){
        dfs(to, !isBlack);
    }
}

int main(){
    cin >> N;
    for(int i=0; i<N-1; i++){
        int u, v;
        cin >> u >> v;
        adj[min(u,v)].push_back(max(u,v));
    }
    dfs(1, true);
    cout << (black*(N-black))-(N-1) << endl;
    return 0;
}
```

### 拓扑排序

**任务：**

在一个家族中，给出每个人的后代的信息。输出一个序列，使得每个人的后辈都比那个人后列出。如果有多种不同的序列，输出任意一种即可。

**分析：**

首先找到祖先，换句话说在这个有向无环图中找到一个入度为0的点，将其加入答案队列，再将它的所有儿子入度减一。

再次找到一个入度为0的点，将其加入答案队列，再将它的所有儿子入度减一。

如此循环，直到处理完。

**代码：**

```cpp
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

int N;
int in[105];

class edge{
    public:
    int v, next;
    edge(int v = 0, int next = 0){
        this->v = v;
        this->next = next;
    }
};

edge e[10000];
int cnt, head[105];
vector<int> ans;

void addedge(int u, int v){
    e[++cnt] = edge(v, head[u]);
    head[u] = cnt;
}

void toposort(){
    queue<int> q;

    for(int i=1; i<=N; i++){
        if(in[i] == 0) {
            q.push(i);
            ans.push_back(i);
        }
    }

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = head[u]; i ; i = e[i].next){
            int v = e[i].v;
            in[v]--;
            if(in[v] == 0){
                q.push(v);
                ans.push_back(v);
            }
        }
    }
}

int main(){
    cin >> N;
    for(int i = 1; i <= N; i++){
        int son;
        while(1){
            cin >> son;
            if(son == 0) break;
            addedge(i, son);
            in[son]++;
        }
    }
    toposort();
    for(int i: ans) cout << i << " ";

    return 0;
}
```

> 例题：洛谷B3644 【模板】拓扑排序 / 家谱树
>
> https://www.luogu.com.cn/problem/B3644

## 数学

### 最大公约数 gcd

------

**任务：**

给定正整数 $a$ 和 $b$ ，找出它们的最大公约数，要求$O(log\, n)$时间复杂度

**代码：**

```cpp
int gcd(int a, int b){
    if(a%b==0)return b;
    return gcd(b,a%b);
}
```

最小公倍数 = $a \times b \div gcd(a, b)$

> 练练手？洛谷P1029 [NOIP2001 普及组] 最大公约数和最小公倍数问题
>
> https://www.luogu.com.cn/problem/P1029

补充：对余数的观察：

```cpp
cout << (5%3) << endl; // 2
cout << (-5%3) << endl;// -2
cout << (5%-3) << endl;// 2
cout << (-5%-3) << endl;// -2
```

只有前面的负号在管事，同样的：

```cpp
cout << gcd(12, 8) << endl; // 4
cout << gcd(12, -8) << endl;// 4
cout << gcd(-12, 8) << endl;// -4
cout << gcd(-12, -8) << endl;// -4
cout << gcd(8, 12) << endl;// 4
cout << gcd(8, -12) << endl;// -4
cout << gcd(-8, 12) << endl;// 4
cout << gcd(-8, -12) << endl;// -4
```

管事的是绝对值较大的数的符号。

**扩展欧几里得算法（egcd）**：对于不全为 0 的非负整数 a，b，gcd（a，b）表示 a，b 的最大公约数，必然存在整数对 x，y ，使得 gcd（a，b）=xa+yb。

证明：

设 a>b
显然当 b=0，gcd（a，b）=a。此时 x=1，y=0；
ab!=0 时
设 $ax_1+by_1=gcd(a,b)$
$bx_2+(a \mod b)y_2=gcd(b,a \mod b)$
则:$ax_1+by_1=bx_2+(a \mod b)y_2$
即:
$$
ax_1+by_1=bx_2+(a-\lfloor a/b \rfloor*b)y_2=ay_2+bx_2-\lfloor a/b \rfloor*by_2
$$
根据恒等定理得：
$$
x1=y2\\ y1=x2-\lfloor a/b \rfloor*y2;
$$
代码：

```cpp
pair<int,int> egcd(a, b){
    if(a%b==0) return make_pair(1,0);
    pair<int, int> p = egcd(b, a%b);
    return make_pair(p.second, p.first-(a/b)*p.second);
}
```

### 裴蜀定理(贝祖定理)

------

**定理内容：**

$ax+by=c,x \in Z^{*},y \in Z^{*}$ 成立的充要条件是 $gcd(a,b)|c$

可以扩展到更多元

> 练练手？洛谷P4549 【模板】裴蜀定理
>
> 给定一个包含 $n$ 个元素的**整数**序列 $A$，记作 $A_1,A_2,A_3,...,A_n$。
>
> 求另一个包含 $n$ 个元素的待定**整数**序列 $X$，记 $S=\sum\limits_{i=1}^nA_i\times X_i$，使得 $S>0$ 且 $S$ 尽可能的小。
>
> https://www.luogu.com.cn/problem/P4549

### 欧拉筛法

------

**任务：**

给定正整数$n$，找到所有小于等于$n$的素数，要求$O(n)$时间复杂度

**分析：**

朴素的想法是对每一个数 $i$ ，用所有已知的素数测试，但这不满足$O(n)$时间复杂度

考虑有一个数 $i$，用很多其他数 $j$ 乘它，$i\times j$ 肯定不是素数

那么就可以假定所有数都是素数，去掉不是素数的，剩下的就是素数

**代码：**

```cpp
const int MAX = 1e7+5;
bool not_prime[MAX];
int prime_size;
int prime[MAX];

void sieve(int n){
    for(int i = 2; i <= n; ++i){
        if(!not_prime[i]) prime[++prime_size] = i;//这个模板prime数组从1开始有效
        for(int j = 1; j <= prime_size && i * prime[j] <= n; ++j){
            not_prime[i * prime[j]] = 1;
            if(i % prime[j] == 0) break;
        }
    }
}
```

> 练练手？洛谷P3383 【模板】线性筛素数
>
> https://www.luogu.com.cn/problem/P3383

### 快速幂

------

**任务：**

计算 $n^m$ ，要求时间复杂度为 $O(log\, n)$

**分析：**

如果一个一个乘，时间复杂度$O(n)$，肯定超过1秒

但是考虑 $2^5 = 2 \times 2 \times 2\times 2\times 2 = 4\times 4\times 2$

以及考虑 $2^{11} = \underbrace{2\times2\ldots\times2}_{11} = 2^5 \times 2^5 \times 2$

如果已经算出$2^5$，那就不用再从头算了

每次将$m$除2，算出中间结果直接再算，将时间复杂度降为$O(log\, n)$

**代码（注意，这份代码没有取MOD，没有用long long，做题时请加上）：**

```cpp
int qpow(int a, int b) {
    if (b == 0) return 1;
    int x = qpow(a, b >> 1);
    if (b & 1)return  x * x * a;
    return x * x;
}
```

> 练练手？洛谷P1226 【模板】快速幂||取余运算
>
> https://www.luogu.com.cn/problem/P1226

### 费马小定理

------

如果$p$是一个质数，而整数$a$不是$p$的倍数，则有：
$$
a^{p-1}\equiv b\pmod p
$$
当然，在算法竞赛，它的应用是对**分数取模**：
$$
\frac{b}{a}\pmod p = b\times a^{p-2}\pmod p
$$
换种说法，一个数$a$的**逆元**为$a^{p-2}$

### 康托展开

------

**任务：**

对$1,2,3\ldots n$ 共$n$个数，随机给出一个序列，找出其上一个字典序

**分析：**

试图找出当前排列在所有排列中的排名$score$

对于序列24513，从第一个数向后看，比2小的有一个数，$score+=1\times4!$ 

现在看第二个数，比4小的一共三个数，但2已经出现，所以剩两个数，$score+=2\times3!$

类推，$score$最后表示当前序列前面有多少个序列

由$score$反推序列就是逆康托展开，思想相同

**代码：**

> 例题：洛谷P2525 Uim的情人节礼物·其之壱
>
> https://www.luogu.com.cn/problem/P2525

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int N;
int nums[15];
int vis[15];
int ans[15];
int score = 0;

int step_mul(int a){
    if(a == 0) return 1;
    int ta = a;
    while(a-- > 1) ta *= a;
    return ta;
}

void conto(){
    for(int i = 1; i <= N; ++i){
        vis[nums[i]] = 1;
        int cnt = 0;
        for(int j = nums[i] - 1; j > 0; --j){
            if(!vis[j]) cnt++;
        }
        score += cnt * step_mul(N - i);
    }
}

void re_conto(){
    for(int i = 1; i <= N; ++i){
        int cnt = score / step_mul(N - i);
        score %= step_mul(N - i);
        int index = 1;
        while (cnt > 0) {
            while (vis[index]) index++;
            if(!vis[index]) cnt--;
            index++;
        }
        while (vis[index]) index++;
        ans[i] = index;
        vis[index] = 1;
    }
}

int main(){
    cin >> N;
    for(int i = 1; i <= N; ++i)cin >> nums[i];
    conto();
    score--;
    memset(vis, 0, sizeof(vis));
    re_conto();
    for(int i = 1; i <= N; ++i) cout << ans[i] << " ";
    
    return 0;
}
```

> STL?

```cpp
if(prev_permutation(a,a+n))		//如果为真就输出数组
	for(int i=0;i<n;i++) cout<<a[i]<<" ";
else cout<<"ERROR";				//否则输出ERROR
```

### 容斥定理

------

**任务：**

错排问题：对一个有序序列$1,2,3\ldots n$ ，打乱它，使所有数都不在原来的位置上，求这种序列数量（$D_n$）

**分析：**

容斥定理告诉我们：
$$
D_n = n!(1-\frac{1}{1!}+\frac{1}{2!}-\frac{1}{3!}+...+(-1)^n\frac{1}{n!})
$$
意思是：
$$
全乱 = 全序列 - \sum 有一个数在原来位置（带重叠）+\sum 有两个数（带重叠）\ldots +(-1)^n\sum 全齐 \\
全序列 = A_n^n=n!\\
\sum 有一个数在原来位置（带重叠）=选一个数固定，剩下全排列 = C_n^1A_{n-1}^{n-1}\\
全齐 = A_n^0 = 1
$$
当然，在算法竞赛时使用它的递推式来做更方便：
$$
D_0=1,D_1=0,D_2=1\\
D_n=(n-1)(D_{n-1}+D_{n-2}) ~ (n=3,4,5,...)
$$
**代码：**

> 例题：洛谷[SDOI2016]排列计数
>
> https://www.luogu.com.cn/problem/P4071
>
> 求有多少种 $1$ 到 $n$ 的排列 $a$，满足序列恰好有 $m$ 个位置 $i$，使得 $a_i = i$。答案对 $10^9 + 7$ 取模。
>

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

int T, N, M;
const int MAX = 1e6+10;
ll p = 1e9+7;
ll D[MAX];
ll jcs[MAX];

//快速幂
ll qpow(ll a, ll b) {
    if (b == 0) return 1;
    ll x = qpow(a, b >> 1);
    if (b & 1)return (x * x % p) * a % p;
    return (x * x) % p;
}

int main(){
    D[0] = 1;D[1] = 0;D[2] = 1;
    for(int i = 3; i < MAX; ++i) D[i] = (i-1)*(D[i-1]+D[i-2])%p;//容斥定理
    jcs[0] = 1;
    for(int i = 1; i < MAX; ++i) jcs[i] = jcs[i-1]*i%p;//阶乘预处理
    
    cin >> T;
    while (T--) {
        scanf("%d%d", &N, &M);
        cout << ((jcs[N]*qpow(jcs[M]*jcs[N-M]%p, p-2)%p) * D[N-M]) % p << endl;//逆元
    }
    
    return 0;
}
```

### 组合数

------

**任务：**

给定 $n,m$ 和 $k$，对于所有的 $0\leq i\leq n,0\leq j\leq \min \left ( i, m \right )$  求有多少对 $(i,j)$ 满足 $k|C_{i}^{j}$

**分析：**

已知**基本公式：**
$$
A_n^m=\frac{n!}{(n-m)!}\\
C^m_n=\frac{n!}{m!(n-m)!}
$$
常见的优化时间方法是预处理组合数$C$，使用**递推公式**，注意初始化：
$$
C^0_0=0,C^0_i=C^0_1=C^1_1=1\\
C^m_n=C^{m-1}_{n-1}+C^m_{n-1}
$$
如果数据量极大，考虑**前缀和**，因为任务是二维结构，使用**二维前缀和**

**代码：**

> 例题：洛谷P2822 [NOIP2016 提高组] 组合数问题
>
> https://www.luogu.com.cn/problem/P2822

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int T, K, N, M;
const int MAX = 2e3+10;
int C[MAX][MAX];
int ans[MAX][MAX];

void build_C(){
    C[0][0] = C[1][0] = C[1][1] = 1;
    for(int i = 2; i < MAX; ++i){
        C[i][0] = 1;
        for(int j = 1; j <= i; ++j){
            ans[i][j] = ans[i-1][j] + ans[i][j-1] - ans[i-1][j-1];//二维前缀和
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % K;//预处理组合数
            if(C[i][j] == 0) ans[i][j]++;
        }
        ans[i][i+1] = ans[i][i];
    }
}

int main(){
    cin >> T >> K;
    build_C();
    while (T--) {
        scanf("%d%d", &N, &M);
        if(M > N) cout << ans[N][N] << endl;
        else cout << ans[N][M] << endl;
    }
    return 0;
}
```

### 卢卡斯定理

------

**定理内容：**
$$
C_a^b\equiv C_{\lfloor \frac{a}{p} \rfloor}^{\lfloor \frac{b}{p} \rfloor}\cdot C_{a~mod~p}^{b~mod~p}(mod~p)
$$
Lucas定理的主要用途在于在 $O(\log_p a)$ 的时间求出 $C_a^b \mod p$ 的结果

**代码：**

> 例题：洛谷P3807 【模板】卢卡斯定理/Lucas 定理
>
> https://www.luogu.com.cn/problem/P3807

```cpp
#include <iostream>
using namespace std;
typedef long long ll;

int T;
ll n, m, p;

//快速幂
ll qpow(ll a, ll b) {
    if (b == 0) return 1;
    ll x = qpow(a, b >> 1);
    if (b & 1)return (x * x % p) * a % p;
    return x * x % p;
}

ll C(ll n, ll m){
    if(n < m) return 0;
    if(m > n - m) m = n - m;
    ll a = 1,b = 1;
    for(int i = 0; i < m; i++){
        a = a * (n - i) %p;
        b = b * (i + 1) %p;
    }
    return a * qpow(b, p-2) %p;//逆元
}

ll lucas(ll n,ll m){
    if(m == 0) return 1;
    return lucas(n/p,m/p) * C(n%p,m%p) %p;
}

int main(){
    cin >> T;
    while (T--) {
        cin >> n >> m >> p;
        cout << lucas(n + m, m) << endl;
    }
    return 0;
}
```

### 进制转换

```cpp
while(n!=0){
    d[len++]=n%radix;
    n/=radix;
}
for(int i=0;i<len;i++){
    n=n*radix+d[i];
}
```

### 位运算

**位与（&）运算** ：&运算通常用于二进制取位操作，例如一个数 & 1的结果就是取二进制的最末位。这可以用来判断一个整数的奇偶，二进制的最末位为0表示该数为偶数，最末位为1表示该数为奇数。

**位或（|）运算**：|运算通常用于二进制特定位上的无条件赋值，例如一个数 | 1的结果就是把二进制最末位强行变成1。如果需要把二进制最末位变成0，对这个数| 1之后再减一就可以了，其实际意义就是把这个数强行变成最接近的偶数。

**位异或（^）运算**：^运算通常用于对二进制的特定一位进行取反操作，因为异或可以这样定义：两个数的二进制位相同则结果为 0，不同则结果为 1。   ^运算的逆运算是它本身，也就是说两次异或同一个数最后结果不变，即(a ^ b) ^ b = a。

> 如何不借助中间变量 交换两个数呢？
>
> ```cpp
> void swap(int a, int b){
> 	a=a + b; b=a - b; a=a - b;
> }
> void swap(int a, int b){
> 	a=a ^ b; b=a ^ b; a=a ^ b;
> }
> ```

**位取反（~）运算**：   ~运算的定义是把内存中的0和1全部取反。使用~运算时要格外小心，你需要注意整数类型有没有符号。 最常见的用法是`while(~ scanf(“%d” ,&n)){}`

**位左移（<<）运算**： a << b就表示把a转为二进制后左移b位（在后面添b个0）。例如100的二进制为1100100，而110010000转成十进制是400，那么100 << 2 = 400。可以看出，a << b的值实际上就是a乘以2的b次方，因为在二进制数后添一个0就相当于该数乘以2。  

通常认为a << 1比a * 2更快，因为前者是更底层一些的操作。因此程序中乘以2的操作请尽量用左移一位来代替。   

定义一些常量可能会用到<<运算。你可以方便地用1 << 16 - 1来表示65535。很多算法和数据结构要求数据规模必须是2的幂，此时可以用<<来定义Max_N等常量。

**位右移（>>）运算** ：和<<相似，a >> b表示二进制右移b位（去掉末b位），相当于a除以2的b次方（取整）。我们也经常用>> 1来代替整除 2，比如二分查找、堆的插入操作等等。想办法用>>代替除法运算可以使程序效率大大提高。最大公约数的二进制算法用除以2操作来代替慢得出奇的求余运算，效率可以提高60%。

位运算优先级别：   

位反 > 算术 > 位左移、位右移 > 关系运算 > 位与 > 位或 > 位异或 > 逻辑运算

**任务：**

现在教室里有N个人，选出其中的一些人来搬书，所有的组合方法有哪些？

**代码：**

```cpp
#include<iostream>
#include<cstring>
using namespace std;

int n;
int c[100];

void count(int x){
    memset(c,0,sizeof(c));
    for(int i=0;i<n;i++)if(x&(1<<i))c[i]=1;
}

int main(){
    cin>>n;
    for(int i=0;i<(1<<n);i++){
        count(i);
        for(int j=0;j<n;j++)cout<<c[j];
        cout<<endl;
    }
    return 0;
}
```

**任务：**

枚举一个集合的子集和对应的补集

**代码：**

```cpp
// S 为全集，S1 为子集，S2 为对应的补集
for(int S1=S;S1!=0;S1=(S1-1)&S){
    S2=S^S1;  
}
// 如果两个数a，b，a<b，对这两个数进行&运算，最后的结果一定是b的子集
```

### 简单的大数加模拟

```cpp
// a 和 b 同位
string add(string a, string b){
    string res;
    int carry = 0;
    for(int i = a.size() - 1; i >= 0; i--){
        int sum = a[i] - '0' + b[i] - '0' + carry;
        res.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    if(carry) res.push_back(carry + '0');
    reverse(res.begin(), res.end());
    return res;
}
```



## STL常用容器操作

### set

------

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

------

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

------

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

