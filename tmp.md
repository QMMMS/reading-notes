# start

因此：

$$
\mathcal{D}^m(\{S|_x : L_{(\mathcal{D}, f)}(h_S) > \epsilon\}) \leq \mathcal{D}^m(M) = \mathcal{D}^m(\bigcup_{h \in \mathcal{H}_B} \{S|_x : L_S(h) = 0\})
$$

由于 $$\mathcal{D}(A\cup B) \leq \mathcal{D}(A) + \mathcal{D}(B)$$，那么：

$$
\mathcal{D}^m(\{S|_x : L_{(\mathcal{D}, f)}(h_S) > \epsilon\}) \leq \sum_{h \in \mathcal{H}_B} \mathcal{D}^m(\{S|_x : L_S(h) = 0\})
$$

又因为：

$$
\begin{align}
\mathcal{D}^m(\{S|_x : L_S(h) = 0\}) &= \mathcal{D}^m(\{S|_x : \forall i, h(x_i) = f(x_i)\}) \\
&= \prod_{i=1}^m \mathcal{D}(\{x_i : h(x_i) = f(x_i)\})
\end{align}
$$

在我们之前的定义中：

$$
\mathcal{D}(\{x_i : h(x_i) = y_i\}) = 1 - L_{(\mathcal{D}, f)}(h) \leq 1 - \epsilon
$$

又因为 $$ 1 - \epsilon \leq e^{-\epsilon} $$，所以：

$$
\mathcal{D}^m(\{S|_x : L_S(h) = 0\}) \leq (1 - \epsilon)^m \leq e^{-\epsilon m}
$$

最终，我们找到了这个上界：

$$
\mathcal{D}^m(\{S|_x : L_{(\mathcal{D}, f)}(h_S) > \epsilon\}) \leq |\mathcal{H}_B| e^{-\epsilon m} \leq |\mathcal{H}| e^{-\epsilon m}
$$

用图来解释，大圆中的每个点代表一个可能的实例 m 元组。每个彩色椭圆表示“误导”实例 m 元组的集合，会导致某个“糟糕”的预测器 $$ h \in \mathcal{H}_B $$ 。每当遇到误导性的训练集 S 时，ERM 可能会发生过拟合。

也就是说，对于某些 $$ h \in \mathcal{H}_B $$，我们有 $$L_S​(h)=0$$。上界保证了对于每个单独的糟糕假设 $$ h \in \mathcal{H}_B $$​，最多有 $$(1 - \epsilon)^m$$ 比例的训练集会产生误导。特别地，m 越大，这些彩色椭圆的大小就越小。并集界限形式化了这样一个事实：对于某些 $$ h \in \mathcal{H}_B $$​（即，集合 M 中的训练集）而言，误导性训练集的区域大小最多是这些彩色椭圆区域的总和。因此，它被 $$|\mathcal{H}_B|$$ 乘以最大椭圆大小所界定。任何椭圆外的样本 S 都不会导致 ERM 规则过拟合。

由此产出的推论为，当我们取一个足够大的 m，在一个有限的假设类 $$ \mathcal{H} $$上，我们有 $$1-\delta$$ 的概率，认为 $$ERM_{\mathcal{H}}$$ 的损失小于 $$\epsilon$$

# PAC

> 在前一章中，我们已经证明，对于一个有限的假设类，如果将 ERM 规则应用于足够大的训练样本（其大小独立于基础分布或标记函数），那么输出假设可能会是大致正确的。

更一般地，我们现在定义可能大致正确（PAC, Probably Approximately Correct）学习，一个假设类 $$ \mathcal{H} $$ 是 PAC 可学习的，那么：

- 如果存在一个函数 $$m_{\mathcal{H}} : (0,1)^2 \to \mathbb{N}$$ 

- 并存在一个具有以下性质的学习算法：对于每个 $$\epsilon, \delta \in (0,1)$$ 和每个在 $$\mathcal{X} $$ 上的分布 $$ \mathcal{D} $$，以及对于每个标记函数 $$f : \mathcal{X} \to \{0,1\}$$，可实现假设成立

- 在运行学习算法时，需满足 $$m \geq m_{\mathcal{H}}(\epsilon, \delta)$$ 个由 $$ \mathcal{D} $$ 生成并由 f 标记的独立同分布样例

那么，算法可以返回一个假设 $$ \mathcal{h} $$，使得以至少 $$1-\delta$$ 的概率，有 $$L_{(\mathcal{D},f)}(h) \leq \epsilon$$

## 样本复杂度

其中，函数 $$m_{\mathcal{H}} : (0,1)^2 \to \mathbb{N}$$  决定了学习 $$ \mathcal{H} $$ 的样本复杂度，也就是说，需要多少样本才能保证一个可能大致正确的解决方案。样本复杂度是关于精度 $$\epsilon$$ 和置信度 $$\delta$$ 的函数。它还取决于假设类 $$ \mathcal{H} $$ 的属性（例如，对于一个有限类，我们已经表明样本复杂度取决于 $$ \mathcal{H} $$ 大小的对数）

注意，如果 $$ \mathcal{H} $$ 是 PAC 可学习的，那么有许多函数 $$m_H$$ 满足 PAC 可学习性的定义中的要求。因此，为了精确起见，我们将学习 $$ \mathcal{H} $$ 的样本复杂度定义为“最小函数”，也就是说，对于任何 $$\epsilon, \delta$$，$$m_{\mathcal{H}}(\epsilon, \delta)$$是满足具有精度和置信度的 PAC 学习要求的最小整数。即：
$$
m_{\mathcal{H}}(\epsilon, \delta) \leq \left\lceil \frac{\log(|\mathcal{H}|/\delta)}{\epsilon} \right\rceil
$$

## 去除可实现性假设

现在我们尝试泛化 PAC。之前，我们要求学习算法满足可实现性假设，对于一对数据分布 $$ \mathcal{D}$$  和标记函数 f 能够成功工作。现在，我们将放弃这一可实现性假设，即不可知（agnostic） PAC 模型。

> 回忆一下，可实现性假设要求存在一个 $$h^* \in \mathcal{H}$$，使得 $$\mathbb{P}_{x \sim \mathcal{D}}[h^*(x) = f(x)] = 1$$

我们通过用更灵活的数据-标签生成分布替代“目标标记函数”来放松可实现性假设。正式地，让 $$ \mathcal{D}$$ 成为 $$\mathcal{X} \times \mathcal{Y}$$ 上的概率分布，分别代表域集合和标签集合（通常我们考虑 $$\mathcal{Y} = \{0,1\}$$）。也就是说，$$ \mathcal{D}$$ 是域点和标签的联合分布。这种分布可以视为由两部分组成：

- 未标记域点的分布 $$ \mathcal{D}_x$$（有时称为边缘分布）
- 每个域点的标签的条件概率 $$\mathcal{D}((x,y)|x)$$

> 在木瓜的例子中，前者确定了木瓜的颜色和硬度落在某些颜色-硬度值域中的概率，后者表示某个颜色和硬度的木瓜是美味的概率

重新定义 true error：
$$
L_{\mathcal{D}}(h) \overset{\text{def}}{=} \mathbb{P}_{(x,y) \sim \mathcal{D}}[h(x) \neq y] \overset{\text{def}}{=} \mathcal{D}(\{(x,y) : h(x) \neq y\})
$$
empirical risk 因为只知道训练集，本来就不知道数据的分布，所以与原来一致：
$$
L_{S}(h) \overset{\text{def}}{=} \frac{\left|\{i \in [m] : h(x_i) \neq y_i\}\right|}{m}
$$
我们的目标还是最小化$$L_{\mathcal{D}}(h)$$，实际上，可以证明，最优的标签预测函数，即贝叶斯最优预测器 $$f_{\mathcal{D}}$$ 是：
$$
f_{\mathcal{D}}(x) = 
\begin{cases} 
1 & \text{if } \mathbb{P}[y = 1 | x] \ge 1/2 \\ 
0 & \text{otherwise} 
\end{cases}
$$
没有比它错误率更低的分类器了，然而，由于不知道 $$ \mathcal{D}$$，没法得到它。我们现在可以给出不可知 PAC 可学习性的正式定义：

当存在一个函数 $$m_{\mathcal{H}} : (0,1)^2 \to \mathbb{N}$$  和一个学习算法，具有以下性质时，一个假设类 $$ \mathcal{H} $$ 是不可知 PAC 可学习的：于每一个 $$\epsilon, \delta \in (0,1)$$ 和每一个在 $$\mathcal{X} \times \mathcal{Y}$$ 上的分布 $$ \mathcal{D} $$，当在由 $$ \mathcal{D} $$ 生成的  $$m\geq m_{\mathcal{H}}(\epsilon, \delta)$$ 个独立同分布的样本上运行学习算法时，该算法返回一个假设 $$h$$，使得在至少 $$1-\delta$$ 的概率下：
$$
L_{\mathcal{D}}(h) \le \min_{h' \in \mathcal{H}} L_{\mathcal{D}}(h') + \epsilon
$$

## 其他形式的任务

我们之前的例子都是西瓜甜不甜，模型是二分类的，只需要给出 0/1。其他任务类型包括：

- 多分类
- 回归，$$L_{\mathcal{D}}(h) \overset{\text{def}}{=} \mathbb{E}_{(x,y) \sim \mathcal{D}} (h(x) - y)^2$$

现在我们泛化模型损失loss：

给定任意集合 $$ \mathcal{H} $$和某个域 $$Z$$，令损失函数 $$\ell$$ 为从 $$\mathcal{H} \times Z$$ 到非负实数集的任意函数（$$\ell : \mathcal{H} \times Z \to \mathbb{R}_{+}$$ ）注意，对于预测问题，我们有 $$Z=\mathcal{X} \times \mathcal{Y}$$。然而，我们对损失函数的概念超出了预测任务的范围，因此允许 $$\mathcal{X} \times \mathcal{Y}$$ 是任何示例域

我们现在定义风险函数（risk function）为一个分类器 $$ h \in \mathcal{H}$$  在概率分布$$ \mathcal{D} $$ 下的期望损失：
$$
L_{\mathcal{D}}(h) \overset{\text{def}}{=} \mathbb{E}_{z \sim \mathcal{D}} [\ell(h, z)]
$$
同样，我们定义经验风险为给定样本 $$S=\{z_1,...z_m\} \in Z^m$$ 的期望损失，即：
$$
L_{S}(h) \overset{\text{def}}{=} \frac{1}{m} \sum_{i=1}^{m} \ell(h, z_i)
$$

> 例如，0-1 loss function：
> $$
> \ell_{0-1}(h, (x, y)) \overset{\text{def}}{=} 
> \begin{cases} 
> 0 & \text{if } h(x) = y \\ 
> 1 & \text{if } h(x) \neq y 
> \end{cases}
> $$
> 方差损失：
> $$
> \ell_{\text{sq}}(h, (x, y)) \overset{\text{def}}{=} (h(x) - y)^2
> $$

## 带泛化损失的不可知 PAC 可学习性

现在我们将上面两个章节结合起来，得出 Agnostic PAC Learnability for General Loss Functions 定义：



