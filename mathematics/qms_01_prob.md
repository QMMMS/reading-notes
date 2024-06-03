# 概率与统计基础

## 基础概念

### 独立

设$A$，$B$是随机试验中的两个事件，若满足$$P(AB)=P(A)P(B)$$，则称事件$A$和$B$相互独立。

> 三个及以上事件独立性证明？

### 条件概率

条件概率就是知道了**一定信息**下得到的随机事件的概率。为事件$B$发生条件下事件$A$发生的条件概率：
$$
P(A|B)=\frac{P(AB)}{P(B)}
$$

### 全概率

**两两不相容**的一组事件分割A的样本空间。
$$
P(A)=\sum_{i=1}^{n}P(A|B_i)P(B_i)
$$

### 贝叶斯公式

条件概率公式+全概率公式：
$$
P(B_i|A)=\frac{P(A|B_i)P(B_i)}{\sum_{j=1}^{n}P(A|B_j)P(B_j)}
$$

### 古典概型

设一个试验有*N*个等可能的结果，而事件$E$恰包含其中的$M$个结果，则事件$E$的概率，记为$P(E)$，定义为
$$
P(E)=M/N
$$
古典概型有**两个条件**：

* 有限性，试验结果只有有限个（记为*n*），
* 等可能性，每个基本时间发生的可能性相同。

## 随机变量及其分布

随机变量（random variable）表示随机试验各种**结果的实值单值函数**。例如某一时间内公共汽车站等车乘客人数，电话交换台在一定时间内收到的呼叫次数，灯泡的寿命等等，都是随机变量的实例。

### 离散型随机变量

设$X$为一随机变量，如果$X$**只取有限个或可数个值**，则称$X$为一个（一维）离散型随机变量。

概率函数：
$$
P(X=a_i)=p_i,i=1,2,...
$$
分布函数：
$$
F(X)=P(X\leq x)\quad(-\infty<x<\infty)
$$

### 连续型随机变量

设$X$为一随机变量，$X$**不仅有无限个而且有不可数个值**，则称$X$为一个连续型随机变量。

分布函数：
$$
F(x)=\int_{-\infty}^xf(u)du,\quad-\infty<x<+\infty
$$
密度函数：
$$
f(x)=F'(x)
$$

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

