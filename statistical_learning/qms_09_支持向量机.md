# 支持向量机

## 最大间隔分类器

### 超平面

p维的超平面是p−1维的平面仿射子空间

比如二维超平面：
$$
β_0+β_1X_1+β_2X_2=0
$$
p维超平面：
$$
β_0+β_1X_1+β_2X_2+...+β_pX_p=0
$$
使用超平面分类数据点
$$
β_0+β_1X_1+β_2X_2+...+β_pX_p>0，如果y_i=1
$$

$$
β_0+β_1X_1+β_2X_2+...+β_pX_p<0，如果y_i=-1
$$

等价于
$$
y_i(β_0+β_1X_1+β_2X_2+...+β_pX_p)>0
$$

### 最大间隔超平面

某种意义上说是能够插入两个类别之间的最宽的平板的中线

构建最大间隔分类器，就是如下优化问题的解
$$
\mathop{maximize}\limits_{β_0,β_1,...,β_p}M
$$
满足
$$
\sum_{j=1}^{p}β_j^2=1
$$

$$
y_i(β_0+β_1X_{i1}+β_2X_{i2}+...+β_pX_{ip})≥M,i=1,...,n
$$

$y_i(β_0+β_1X_{i1}+β_2X_{i2}+...+β_pX_{ip})$ 在加上 $\sum_{j=1}^{p}β_j^2=1$ 可以证明为第 i 个观测到超平面的距离

M大于0，代表了超平面的间隔，优化问题就是找出最大化M时的$β_0,β_1,...,β_p$

可能存在线性不可分的情况

## 支持向量分类器

为了提高分类器对单个观测分类的稳定性以及使大部分训练观测更好地被分类，允许被误分类
$$
\mathop{maximize}\limits_{β_0,β_1,...,β_p}M
$$
满足
$$
\sum_{j=1}^{p}β_j^2=1
$$

$$
y_i(β_0+β_1X_{i1}+β_2X_{i2}+...+β_pX_{ip})≥M(1-ε_i)
$$

$$
ε_i≥0,\sum_{i=1}^{n}ε_i≤C
$$

C是非负的调节参数，C增大，允许穿过间隔的点就更多，方差减小偏差增大

$ε_i$是松弛变量，允许小部分观测可以落在间隔错误或是超平面错误的一侧

### 支持向量

刚好落在间隔上和落在间隔错误一侧的观测叫做**支持向量**，只有这些观测会影响支持向量分类器

### 非线性决策边界分类

如果预测变量和响应变量之间的关系是非线性的，可以使用预测变量的高阶多项式来扩大特征空间

比如可以使用2p个特征（多包含了二次项）来得到支持向量分类器：
$$
\mathop{maximize}\limits_{β_0,β_{11},β_{12}，...,β_{p1}，β_{p2},ε_1,ε_2,...,ε_n}M
$$
满足
$$
y_i(β_0+\sum_{j=1}^{p}β_{j1}x_{ij} + \sum_{j=1}^{p}β_{j2}x_{ij}^2)≥M(1-ε_i)
$$

$$
ε_i≥0,\sum_{i=1}^{n}ε_i≤C,\sum_{j=1}^{p}\sum_{k=1}^{2}β_{jk}^2=1
$$

## 支持向量机

是支持向量分类器的一个扩展，使用**核函数**来扩大特征空间

内积：两个p维向量a和b的**内积**定义为
$$
<x_i,x_{i'}>=\sum_{j=1}^{p}x_{ij}x_{i'j}
$$

### 线性支持向量分类器

线性支持向量分类器可以描述为
$$
f(x)=β_0+\sum_{i=1}^{n}α_i<x,x_i>
$$
式子有n个参数$α_i$，每个训练观测对应一个参数

为了估计$α_i$和$β_0$，只需要所有训练观测的$C_n^2$个成对组合的内积$<x_i,x_{i'}>$

注意：非支持向量的观测的$α_i$=0

用一种一般化的形式$K(x_i,x_{i'})$来代替内积，这里K是一个核函数，用来衡量观测之间相似性的函数

比如使用简单的核函数$K(x_i,x_{i'})=\sum_{j=1}^{p}x_{ij}x_{i'j}$（**线性核函数**），即此时核函数就是$x_i$和$x_{i'}$的内积

### 自由度为d的多项式核函数

$$
f(x)=β_0+\sum_{i=1}^{n}α_i K(x,x_{i})
$$

$$
K(x_i,x_{i'})=(1+\sum_{j=1}^{p}x_{ij}x_{i'j})^d
$$

和标准的线性核函数相比，能生成光滑度更高的决策边界

支持向量分类器与这样的非线性核函数的结合，就是**支持向量机**

这种情况下非线性核函数的形式为$f(x)=β_0+\sum_{i∈S}α_iK(x,x_i)$

### 径向核函数

$$
K(x_i,x_{i'})=\exp(-γ\sum_{j=1}^{p}(x_{ij}-x_{i'j})^2)
$$

原理是以欧氏距离衡量，离测试观测远的训练观测的影响很小，某种意义上径向核函数是一种局部方法

### 使用核函数的优势

计算量更小

- 核函数只需要为$C_n^2$个不同对配对$i,i'$计算$K(x_i,x_i')$
- 而在扩大的特征空间中没有明确的计算量

## 多分类的SVM

### 一对一

需要构建$C_k^2$个SVM，每个SVM用来分隔两个类别

然后使用所有SVM对一个测试观测进行分类，最终预测类别就是预测次数最多的那一类

### 一对其余

拟合K个SVM，记$β_{0k},β_{1k},...,β_{pk}$为使用SVM比较第k类与其他k-1类的时候，拟合的参数的结果

记$x^*$为一个测试观测，将这个观测预测为使得$β_{0k}+β_{1k}x_1^*+...+β_{pk}x_p^*$最大化的那个类别
