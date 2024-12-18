# 偏差还是过拟合？

## 没有免费午餐定理

> 复习一下，之前我们学过，减少过拟合的一种方式是使用归纳偏好（Inductive Bias）。预先设定一个假设类 $$\mathcal{H}$$ ，使用经验风险最小化（ERM）的机器学习算法从 $$\mathcal{H}$$ 中选择一个误差最小的预测函数 $$h \in \mathcal{H}$$
>
> 这样的假设类可以视作先验知识——相信 $$\mathcal{H}$$ 中的某个成员是该任务的低误差模型。

先验知识对机器学习算法的成功真的必要吗？是否存在一个不需要先验知识的通用的机器学习算法？即：

对于域 $$\mathcal{X}$$ 上的二元分类任务的学习算法，针对0−1损失，是否存在一个固定的机器算法 $$A$$ ，在任意一个 $$\mathcal{X}\times\{0,1\}$$ 分布 $$\mathcal{D}$$ 上，接收到  $$m$$ （小于 $$|\mathcal{X}|/2$$ ）个独立同分布的样本，能输出一个低损失的预测函数 $$h$$ ?

没有免费午餐定理（The No-Free- Lunch theorem）指出不存在这样的机器学习算法。更准确地说，定理指出，对于二元分类预测任务，对于每个机器学习算法，都存在一个其失败的分布。我们定义一个机器学习算法失败为：

1. 从分布选出 $$m$$ 个样本作为训练集，$$S\sim\mathcal{D}^m$$，至少有1/7的概率，使得 $$L_\mathcal{D}(A(S)) \geq 1/8$$
2. 存在另一个函数 $$f$$ 使得 $$L_\mathcal{D}(h) =0$$

> 换句话说，没有免费午餐定理指出没有机器学习算法能在所有可学习任务上成功——每个机器学习算法都有失败的任务，而其他机器学习算法则成功。

证明在这里省略了，可以看书，证明的思路是，假设 $$C$$ 是大小为 $$2m$$ 的 $$\mathcal{X}$$ 的子集，任何只观察 C 中一半实例的学习算法没有关于 C 中其余实例标签的信息。因此，某个目标函数 $$f$$ ，它的 $$A(S)$$ 预测与 C 上未观察实例标签矛盾。

**推论5.2**：$$ \mathcal{X}$$ 是一个有限的假设类，如果 $$\mathcal{H}$$ 包括$$\mathcal{X}\times\{0,1\}$$ 上所有的函数，不能进一步缩小范围，那么 $$\mathcal{H}$$ 不是 PAC 可学习的。

**推论5.2证明**：复习一下，因为根据PAC可学习性的定义，如果已知存在某个预测函数 $$L_\mathcal{D}(f) = 0$$，那么必须存在某个学习算法 $$A$$ 和整数 $$m = m(\epsilon, \delta)$$，当 $$A$$ 应用于从 $$\mathcal{D}$$ 中生成的大小为 $$m$$ 的独立同分布样本 $$S$$ 时，大于 $$1 - \delta$$ 概率的情况下，有 $$L_\mathcal{D}(A(S)) \leq \epsilon$$。但是，根据没有免费午餐定理，由于 $$|\mathcal{X}| \geq 2m$$，对于每个学习算法（尤其是算法 $$A$$ ），存在一个分布 $$\mathcal{D}$$ ，大于 $$1/7 > \delta$$ 概率的情况下，有 $$L_\mathcal{D}(A(S)) > 1/8 > \epsilon$$

如何防止这种失败？可以使用对特定学习任务的先验知识，以避免在学习该任务时导致失败的分布。这种先验知识可以通过限制假设类 $$\mathcal{H}$$ 来表达。但我们应该如何选择一个好的假设类？

- 一方面，我们希望这个类至少在PAC设置中包含没有误差的假设，或者至少从这个类中可实现的最小误差确实相当小
- 另一方面，我们刚刚看到我们不能简单地选择最丰富的类——给定域上所有函数的类。

对 $$\mathcal{D}$$ 的先验分为几种方式：

- 我们知道分布 $$\mathcal{D}$$ 来自某个特定参数分布族
- 我们知道存在某个预定义假设类 $$\mathcal{H}$$ ，能在可能大致正确学习（PAC）中使 $$L_\mathcal{D}(h) =0$$
- 更柔和的先验知识是，我们知道存在某个预定义假设类 $$\mathcal{H}$$，能在 PAC 中使  $$\min_{h\in\mathcal{H}}L_\mathcal{D}(h)$$ 较小，在某种程度上，这种对 $$\mathcal{D}$$ 的先验是不可知（Agnostic） PAC 模型的前提条件，使得预测函数的损失不会超过 $$\min_{h\in\mathcal{H}}L_\mathcal{D}(h)$$ 很多

## 误差分解

我们研究了使用假设类作为形式化先验知识的方法的优点和缺点。我们将一个假设类上的ERM算法的误差分解为两个部分。
$$
L_\mathcal{D}(h_S) = \epsilon_{\text{app}} + \epsilon_{\text{est}}
$$

- 第一个部分，$$\epsilon_{\text{app}} = \min_{h \in \mathcal{H}} L_D(h)$$，衡量了因为限制在特定类中而面临的风险，通过假设类中的假设的最小风险来衡量，这个部分也称为近似误差（approximation error），或算法对从 $$\mathcal{H}$$ 中选择假设的偏差（bias），扩大假设类可以减少近似误差。在可实现假设下，近似误差为零。然而，在不可知论情况下，近似误差可能很大。
- 第二个部分，$$\epsilon_{\text{est}} = L_\mathcal{D}(h_S) - \epsilon_{\text{app}}$$，是由于过拟合导致的误差，这取决于类 $$\mathcal{H}$$ 的大小或复杂性，被称为估计误差（estimation error），在后续章节中，我们将定义假设类的其他复杂度度量。

两个部分意味着我们需要作出权衡：

- 选择 $$\mathcal{H}$$ 为一个非常丰富或者复杂的类，可以减少近似误差，但增加过拟合的风险
- 选择 $$\mathcal{H}$$ 为一个非常小或者简单的集合，可能增加近似误差（欠拟合），但减少过拟合的潜在风险

在许多情况下，经验研究（ empirical research）专注于为某个特定领域设计好的假设类。在这里，“好”意味着近似误差不会过高的类。这个想法是，尽管我们不是专家，也不知道如何构建最优分类器，但我们对手头的具体问题仍有一些先验知识，这使我们能够设计近似误差和估计误差都不太大的假设类。

> 回到木瓜的例子，我们不知道木瓜的颜色和硬度与其味道的具体关联，但我们知道木瓜是水果，并且基于其他水果的经验，我们推测在颜色-硬度空间中的一个矩形可能是一个好的预测器。
