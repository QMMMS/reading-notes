# 数学

## 最大公约数 gcd

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

## 裴蜀定理(贝祖定理)

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

## 欧拉筛法

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

## 快速幂

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

## 费马小定理

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

## 康托展开

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

## 容斥定理

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

## 组合数

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

## 卢卡斯定理

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

## 进制转换

```cpp
while(n!=0){
    d[len++]=n%radix;
    n/=radix;
}
for(int i=0;i<len;i++){
    n=n*radix+d[i];
}
```

## 位运算

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

## 简单的大数加模拟

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