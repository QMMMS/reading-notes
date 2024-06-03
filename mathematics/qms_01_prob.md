# 概率与统计基础

## 基础概念

**独立**：设$A$，$B$是随机试验中的两个事件，若满足$$P(AB)=P(A)P(B)$$，则称事件$A$和$B$相互独立。

**条件概率**：条件概率就是知道了**一定信息**下得到的随机事件的概率。为事件$B$发生条件下事件$A$发生的条件概率：
$$
P(A|B)=\frac{P(AB)}{P(B)}
$$

**全概率**：**两两不相容**的一组事件分割A的样本空间。
$$
P(A)=\sum_{i=1}^{n}P(A|B_i)P(B_i)
$$

**贝叶斯公式**：条件概率公式+全概率公式：
$$
P(B_i|A)=\frac{P(A|B_i)P(B_i)}{\sum_{j=1}^{n}P(A|B_j)P(B_j)}
$$

**古典概型**：设一个试验有*N*个等可能的结果，而事件$E$恰包含其中的$M$个结果，则事件$E$的概率，记为$P(E)$，定义为
$$
P(E)=M/N
$$
古典概型有**两个条件**：

* 有限性，试验结果只有有限个（记为*n*），
* 等可能性，每个基本时间发生的可能性相同。

## 随机变量及其分布

随机变量（random variable）表示随机试验各种**结果的实值单值函数**。例如某一时间内公共汽车站等车乘客人数，电话交换台在一定时间内收到的呼叫次数，灯泡的寿命等等，都是随机变量的实例。

### 随机变量

- 设$X$为一随机变量，如果$X$**只取有限个或可数个值**，则称$X$为一个（一维）**离散型随机变量**。
- 设$X$为一随机变量，$X$**不仅有无限个而且有不可数个值**，则称$X$为一个**连续型随机变量**。

**概率函数**（离散和连续）：
$$
P(X=a_i)=p_i,i=1,2,...
$$
$$
f(x)=F'(x)
$$

> 连续随机变量的一切取值充满整个样本空间，而这其中有无穷个不可列的实数，因此无法采用分布列表示，采用**概率密度函数**表示。
>
> 概率密度函数不是概率，乘以区间长度微元后就表示概率的近似值，而概率密度函数在一段区间上的积分就是随机变量 X 在这段区间上取值的概率。

**分布函数**（离散和连续）：
$$
F(X)=P(X\leq x)\quad(-\infty<x<\infty)
$$

$$
F(x)=\int_{-\infty}^xf(u)du,\quad-\infty<x<+\infty
$$

> 随机变量的分布函数表述了随机变量的统计规律性，已知一个随机变量的分布函数就可以得知该随机变量落在某一区间的概率。

### 常见分布

$$
\begin{matrix} \hline
  分布名称&概率分布或密度函数&数学期望&方差&特征函数 \\\hline
  退化分布I_c(x)&p_c=1(c为常数)&c&0&{\rm{e}}^{{\rm{i}}t} \\\hline
  伯努利分布(两点分布)&\begin{matrix}\displaystyle p_k=\left\{\begin{matrix}q, &k=0\\p, &k=1\end{matrix}\right.\\0<q<1,q=1-p\end{matrix}&p&pq&p{\rm{e}}^{{\rm{i}}t}+q\\\hline
  二项分布B(n,p)&\begin{matrix}\displaystyle b(k;n,p)=\begin{pmatrix}n\\k\end{pmatrix}p^kq^{n-k}\\k=0,1,\dots,n\\0<q<1,q=1-p\end{matrix}&np&npq&(p{\rm{e}}^{{\rm{i}}t}+q)^n\\\hline
  泊松分布B(\lambda)&\begin{matrix}\displaystyle p(k;\lambda)=\frac{\lambda^k}{k!}{\rm{e}}^{-\lambda}\\k=0,1,2,\dots,\lambda>0\end{matrix}&\lambda&\lambda&{\rm{e}}^{\lambda({\rm{e}}^{{\rm{i}}t}-1)}\\\hline
  几何分布&\begin{matrix}\displaystyle g(k;p)=q^{k-1}p\\k=1,2,\dots\\0<p<1,q=1-p\end{matrix}&\displaystyle \frac{1}{p}&\displaystyle \frac{q}{p^2}&\displaystyle \frac{p{\rm{e}}^{{\rm{i}}t}}{1-q{\rm{e}}^{{\rm{i}}t}}\\\hline
  超几何分布&\begin{matrix}p_k=\frac{\begin{pmatrix}M\\k\end{pmatrix}\begin{pmatrix}N-M\\n-k\end{pmatrix}}{\begin{pmatrix}N\\n\end{pmatrix}},\begin{matrix}M \leqslant N\\n \leqslant N\\M,N,n \in \mathbb{N^*}\end{matrix}\\k=0,1,2,\cdots,\text{min}(M,n)\end{matrix}&\displaystyle \frac{nM}{N}&\displaystyle \frac{nM}{N}\left(1-\frac{M}{N}\right)\cdot\frac{N-n}{N-1}&\displaystyle \sum_{k=0}^{n} \frac{\begin{pmatrix}M\\k\end{pmatrix}\begin{pmatrix}N-M\\n-k\end{pmatrix}}{\begin{pmatrix}N\\n\end{pmatrix}}{\rm{e}}^{{\rm{i}}tk}\\\hline
  帕斯卡分布&\begin{matrix}p_k=\begin{pmatrix}k-1\\r-1\end{pmatrix}p^r q^{k-r}\\k=r,r+1,\cdots\\0<p<1,q=1-p,r \in \mathbb{N^*}\end{matrix}&\displaystyle \frac{r}{p}&\displaystyle \frac{rq}{p^2}&\displaystyle \left(\frac{p{\rm{e}}^{{\rm{i}}t}}{1-q{\rm{e}}^{{\rm{i}}t}}\right)^r\\\hline
  负二项分布&\begin{matrix}p_k=\begin{pmatrix}-r\\k\end{pmatrix}p^r (-q)^{k}\\k=0,1,2,\cdots\\0<p<1,q=1-p,r>0\end{matrix}&\dfrac{rq}{p}&\dfrac{rq}{p^2}&\displaystyle \left(\frac{p}{1-q{\rm{e}}^{{\rm{i}}t}}\right)^r\\\hline
  \begin{matrix}高斯分布\\(正态分布)\\N(\mu,\sigma^2)\end{matrix}&\begin{matrix}\displaystyle p(x)=\frac{1}{\sqrt{2\pi}\sigma}{\rm{e}}^{-\frac{(x-\mu)^2}{2\sigma^2}}\\-\infty <x<\infty,\mu,\sigma>0\end{matrix}&\mu&\sigma^2&\displaystyle {\rm{e}}^{{\rm{i}}\mu t-\frac{1}{2}\sigma^2t^2}\\\hline
  均匀分布U[a,b]&\begin{matrix}\displaystyle p(x)=\left\{\begin{matrix}\frac{1}{b-a}, &a\leqslant x\leqslant b\\0, &\text{otherwise}\end{matrix}\right.\\a<b\end{matrix}&\displaystyle \frac{a+b}{2}&\displaystyle \frac{(b-a)^2}{12}&\displaystyle \frac{{\rm{e}}^{{\rm{i}}tb}-{\rm{e}}^{{\rm{i}}ta}}{{\rm{i}}t(b-a)}\\\hline
  指数分布\mathrm{Exp}(\lambda)&\begin{matrix}\displaystyle p(x)=\left\{\begin{matrix}\lambda {\rm{e}}^{-\lambda x}, &x \geqslant 0\\0, &x<0\end{matrix}\right.\end{matrix}&\lambda ^{-1}&\lambda ^{-2}&\displaystyle \left(1-\frac{{\rm{i}}t}{\lambda}\right)^{-1}\\\hline
  卡方分布(\chi^2分布)&\begin{matrix}p(x)=\left\{\begin{matrix}\displaystyle \frac{1}{2^{\frac{n}{2}}\Gamma \left(\frac{n}{2}\right)}x^{\frac{n}{2}-1}{\rm{e}}^{\frac{-x}{2}}, &x \geqslant 0\\0, &x<0\end{matrix}\right.\\n \in \mathbb{N^*}\end{matrix}&n&2n&(1-2{\rm{i}}t)^{-\frac{n}{2}}\\\hline
  \begin{matrix}\Gamma分布\\\Gamma(r,\lambda)\\r为正整数时为埃尔朗分布\end{matrix}&\begin{matrix}p(x)=\left\{\begin{matrix}\displaystyle \frac{\lambda^r}{\Gamma(r)}x^{r-1}{\rm{e}}^{-\lambda x}, &x \geqslant 0\\0, &x<0\end{matrix}\right.\\r>0,\lambda>0\end{matrix}&r\lambda^{-1}&r\lambda^{-2}&\left(1-\dfrac{{\rm{i}}t}{\lambda}\right)^{-r}\\\hline
  柯西分布&\begin{matrix}\displaystyle p(x)=\frac{1}{\pi}\cdot \frac{\lambda}{\lambda^2+(x-\mu)^2}\\-\infty <x<\infty,\lambda>0\end{matrix}&不存在&不存在&{\rm{e}}^{{\rm{i}}\mu t-\lambda|t|}\\\hline
  t分布&\begin{matrix}\displaystyle p(x)=\frac{\Gamma\left(\frac{n+1}{2}\right)}{\sqrt{n\pi}\Gamma\left(\frac{n}{2}\right)}\left(1+\frac{x^2}{n}\right)^{-\frac{(n+1)}{2}}\\-\infty <x<\infty,n \in \mathbb{N^*}\end{matrix}&0(n>1)&\dfrac{n}{n-2}(n>2)&\\\hline
  帕累托分布&\begin{matrix}p(x)=\left\{\begin{matrix}rA^r\frac{1}{x^{r+1}}, &x \geqslant A\\0, &x<A\end{matrix}\right.\\r>0,A>0\end{matrix}&(r>1时存在)&(r>2时存在)&\\\hline
  F分布&\begin{matrix}p(x)=\left\{\begin{matrix}\displaystyle \frac{\Gamma\left(\frac{k_1+k_2}{2}\right)}{\Gamma\left(\frac{k_1}{2}\right)\Gamma\left(\frac{k_2}{2}\right)}k_1^\frac{k_1}{2}k_2^\frac{k_2}{2}\cdot\frac{x^{\frac{k_1}{2}-1}}{\left(k_2+k_1x\right)^{\frac{k_1+k_2}{2}}}, &x \geqslant 0\\0, &x<0\end{matrix}\right.\\k_1,k_2 \in \mathbb{N^*}\end{matrix}&\begin{matrix}\dfrac{k_2}{k_2-2}\\(k_2>2)\end{matrix}&\begin{matrix}\dfrac{2k_2^2(k_1+k_2-2)}{k_1(k_2-2)^2(k_2-4)}\\k_2>4\end{matrix}\\\hline
  \beta分布&\begin{matrix}p(x)=\left\{\begin{matrix}\displaystyle \frac{\Gamma(p+q)}{\Gamma(p)\Gamma(q)}x^{p-1}(1-x)^{q-1}, &0<x<1\\0, &x\leqslant0 \text{ or }x\geqslant1\end{matrix}\right.\\p>0,q>0\end{matrix}&\dfrac{p}{p+q}&\dfrac{pq}{(p+q)^2(p+q+1)}&\displaystyle \frac{\Gamma(p+q)}{\Gamma(p)}\cdot\sum^{\infty}_{j=0}\frac{\Gamma(p+j)({\rm{i}}t)^j}{\Gamma(p+q+j)\Gamma(j+1)}\\\hline
  对数分布&\begin{matrix}p(x)=\left\{\begin{matrix}\displaystyle \frac{1}{\sigma x \sqrt{2\pi}}{\rm{e}}^{-\frac{(\ln x-\alpha)^2}{2\sigma^2}}, &x > 0\\0, &x\leqslant0\end{matrix}\right.\\\alpha,\sigma>0 \end{matrix}& {\rm{e}}^{\alpha+\frac{\sigma^2}{2}}&{\rm{e}}^{2\alpha+\sigma^2({\rm{e}}^{\sigma^2}-1)}\\\hline
  韦布尔分布&\begin{matrix}p(x)=\left\{\begin{matrix}\displaystyle \alpha\lambda x^{\alpha-1}{\rm{e}}^{-\lambda x^\alpha}, &x > 0\\0, &x\leqslant0\end{matrix}\right.\\\lambda>0,\alpha>0\end{matrix}&\displaystyle \Gamma\left(\frac{1}{\alpha}+1\right)\cdot\lambda^{-\frac{1}{\alpha}}&\displaystyle \lambda^{-\frac{2}{\alpha}}\left[\Gamma\left(\frac{2}{\alpha}+1\right)-\left(\Gamma\left(\frac{1}{\alpha}+1\right)\right)^2\right]\\\hline
  \end{matrix}
$$

**泊松定理**：在伯努利试验中，$$p_n$$代表事件A在试验中出现的概率。在n较大，通常取大于等于100，p较小，通常取小于等于0.1的情况下，如果$$\lim \limits_{n\rightarrow +\infty} np_n = \lambda$$, 则
$$
\lim \limits_{n\rightarrow +\infty}C_n^kp_n^k(1-p_n)^{n-k} = {\lambda^k\over k!}e^{-\lambda}
$$
**指数分布的无记忆性**：
$$
P(X>s+t∣X>s)=P(X>t)
$$
**正态分布的可加性**：

如果多个随机变量分别服从不同的正态分布，如果这些随机变量彼此独立，那么这些随机变量的和也服从正态分布。

> - 二项分布：常用于检查产品合格率、色盲率调查等等 
> - 两点分别：比赛胜率估计 
> - 泊松分布：常用于一天内到达顾客数、铸件上的砂眼数、一天内电路受到电磁波干扰次数等等
> - 超几何分布：用于进行有限总体中进行不放回抽样。 
> - 几何分布：一次伯努利试验中事件 A 首次出现时的试验次数。例如产品不合格率调查。
> - 正态分布：主要应用于统计理论、误差理论等等 
> - 指数分布：常用于随即服务系统、寿命估计、排队论等等

### 多维随机变量

**边缘分布**（离散和连续）：

> 对于**离散型随机向量**，行和与列和就是边缘分布。即固定某个$$x_i$$，即可计算边缘分布

$$
p_X(x_i)=P(X=x_i)=\sum_{j}^{m}P(X=x_i,Y=y_j)=\sum_{j}^{m}p_{ij}=p_{i\cdot},\quad i=1,2,...,n\\
p_Y(y_i)=P(Y=y_i)=\sum_{i}^{m}P(X=x_i,Y=y_j)=\sum_{i}^{m}p_{ij}=p_{j\cdot},\quad j=1,2,...,n
$$

$$
(X,Y)\sim f(x, y)\\
f_X(u)=\int^{+\infty}_{-\infty}f(u,v)dv\\
f_Y(u)=\int^{+\infty}_{-\infty}f(u,v)du\\
$$

若随机变量$$X_1, ...,X_n$$相互**独立**，则（离散和连续）：
$$
P(X_1=x_1,...,X_n=x_n)=P(X_1=x_1)...P(X_n=x_n)
$$

$$
f(x_1,...,x_n)=f_1(x_1)...f_n(x_n),\quad \forall(x_1,...,x_n)\in \R ^n
$$

> **注：**二维正态分布$$N(a,b,\sigma_1^2,\sigma_2^2,\rho )$$的边缘分布密度分别是一维正态分布$$N(a,\sigma_1^2)$$和$$N(b,\sigma_2^2)$$。联合分布可推边缘分布，而边缘分布不可推联合分布。
>
> 二维正态分布中 X Y 独立的充要条件是 $$\rho=0$$

**条件分布**（离散和连续）：
$$
P(X=x_i|Y=y_j)=\frac{P(X=x_i,Y=y_j)}{P(Y=y_j)}=\frac{p_{ij}}{p_{\cdot j}},\quad i=1,2,...
$$

$$
f_{X|Y}(x|y)=\frac{f(x,y)}{f_Y(y)}, \quad f_Y(y)>0.\\
$$

总结：

联合概率是基于两个随机变量及其相互作用的样本空间的概率。边缘概率是多维随机变量的样本空间中，某一个或多个随机变量构成的子空间的概率。
$$
条件=\frac{联合}{边缘}
$$

### 随机变量的函数的概率分布

**离散型分布的情形**：

设$X$的分布律为$$P(X=x_i)=p_i,Y=g(X)$$，则$$Y$$的分布律为
$$
P(Y=y_j)=P(g(X)=y_j)=\sum_{x_i:g(x_i)=y_j}P(X=x_i)=\sum_{i:g(x_i)=y_j}p_i
$$
即把$$Y=g(X_1,...,X_n)$$可以取的不同值找出来，把与某个值相应的全部$$(X_1,...,X_n)$$值的概率加起来，即得$Y$取这个值的概率。

**连续型分布的情形**：

$$X$$有密度函数$$f(x)$$.$$Y=g(x)$$是一个严格单调的函数，因此其反函数$$X=h(Y)$$存在。有密度函数$$l(y)$$为：
$$
l(y)=f(h(y))|h'(y)|.
$$
设$$(X_1,X_2)$$的联合密度函数为$$f(x_1,x_2)$$，$$Y=X_1+X_2$$的密度函数：

$$
l(y)=\int_{-\infty}^\infty f(x_1,y-x_1)dx_1=\int_{-\infty}^\infty f(x,y-x)dx
$$
若$$X_1,X_2$$独立，则
$$
l(y)=\int_{-\infty}^\infty f_1(x)f_2(y-x)dx=\int_{-\infty}^\infty f_1(y-x)f_2(x)dx
$$

## 随机变量的数字特征

**数学期望**：
$$
E(X)=\sum^\infty_{i=1}a_ip_i
$$

$$
E(X)=\int_{-\infty}^\infty xf(x)dx
$$

**方差**：
$$
D(X)=Var(X)=E(X-EX)^2
$$

$$
Var(X)=E(X^2)-(EX)^2
$$

$$\sigma(X)= \sqrt{Var(X)}$$称为标准差。

**矩**：

$$X$$关于$$c$$点的$$k$$阶矩：
$$
E[(X-c)^k]
$$
特别的，$$k$$阶原点矩（一阶原点矩就是期望）：
$$
a_k=E(X^k)
$$
特别的，$$k$$阶中心矩（二阶中心距是方差）：
$$
\mu_k=E[(X-EX)^k]
$$
**协方差**：
$$
Cov(X,Y)=E[(X-EX)(Y-EY)]
$$

$$
Cov(X,Y)=E(XY)-E(X)E(Y)
$$

- 次序无关，即$$Cov(X,Y)=Cov(Y,X)$$
- $$Cov(c_1X+c_2,c_3Y+c_4)=c_1c_3Cov(X,Y)$$
- $$D(X\pm Y)=D(X)+D(Y)\pm 2Cov(X,Y)$$
- $$Cov(X_1+X_2,Y)=Cov(X_1,Y)+Cov(X_2,Y)$$

> 协方差大于零，表示这两个随机变量呈正相关关系，若协方差小于零表示两个随机变量呈负相关关系。而协方差等于零表示不“线性相关”。

**相关系数**：
$$
\rho_{XY} = \frac{Cov(X,Y)}{\sigma_1\sigma_2}
$$

- 若$$X,Y$$不相关：$$\rho_{XY}=0$$，$$Cov(X,Y)=0$$，$$D(X)D(Y)=0$$

> 相关系数可以看作标准化的协方差，它没有量纲，取值范围在[0, 1]。$$\rho_{XY}=1或-1$$时，有严格线性关系。
>
> 独立一定不相关，而不相关不一定独立。例如线性不相关的随机变量可能是非线性相关。最常见的例子就是 Logistics 函数或者二次函数，自变量和因变量计算所得相关系数很低，但是是互相依赖的变量。

## 大数定理和中心极限定理

> 参考：https://blog.csdn.net/xq151750111/article/details/120439438

**切比雪夫不等式**：即使X分布未知，仍可以对距离期望足够远的地方事件出现的概率做出估计：
$$
P\{ \lvert X - \mu \rvert \geq \epsilon \} \leq \frac{\sigma^2}{\epsilon^2}
$$
**切比雪夫大数定律**：说明了对于独立但分布不同的 n 个随机变量，**随机变量的平均值约等于总体期望的平均值**。
$$
\lim_{n \to \infty}P(\lvert \frac{1}{n} \sum_{k=1}^{n}X_k - \frac{1}{n} \sum_{i=1}^{n}E(X_k) \rvert < \epsilon) =1 
$$
**辛钦大数定理**：说明了对于独立同分布且具有均值 a 的 n 个随机变量，当n 很大的时候它们的**算术平均值依概率收敛于均值**。
$$
\lim_{n\to\infty}P\{|\frac{1}{n}\sum\limits_{i=1}^n\xi_i-a|\lt\varepsilon\}=1
$$
**伯努利大数定律**：表明只要随机试验的次数 n 充分大，那么事件 A **频率和概率的绝对偏差很小**，说明在实际应用中，试验次数很大的时候可以用事件的频率来替代事件的概率。
$$
\lim_{n\to\infty}P\{|\frac{\mu_n}{n}-p|\lt\varepsilon\}=1
$$
**独立同分布中心极限定理**： **样本的平均值约等于总体的平均值**。不管总体是什么分布，任意一个总体的样本平均值都会围绕在总体的整体平均值（数学期望）周围，并且呈正态分布。
$$
\lim_{n \to \infty}F_n(x) = \lim_{n \to \infty}P\{\frac{ \sum_{k = 1}^{n}X_k - n \mu}{\sqrt{n} \sigma} \leq x \} = \Phi(x)
$$
等价的：
$$
\sum_{k = 1}^{n}X_k\sim N(n\mu,n\sigma^2)
$$
**棣莫弗-拉普拉斯极限定理**：是独立同分布中心极限定理的特殊情况，当$$X_n\sim B(n,p)$$时：
$$
\lim_{n \to \infty}P\{\frac{X_n - np}{\sqrt{np(1-p)}} \leq x \} = \Phi(x)
$$
