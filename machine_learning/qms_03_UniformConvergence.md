# 一致收敛

之前，我们已经证明了在可实现性假设下，任何有限假设类都是PAC可学习的。在本章中，我们将开发一个通用工具，**一致收敛**，并应用它来证明只要损失函数是有界的，那么具有一般损失函数的不可知PAC模型中的任何有限类都是可学习的。

回想一下，对于一个假设类 $$\mathcal{H}$$，经验风险最小化（ERM）学习范式的工作如下：在收到训练样本 $$S$$ 后，学习算法评估每个 $$h\in\mathcal{H}$$ 在给定样本上的风险（或误差），并输出一个最小化这个经验风险的 $$\mathcal{H}$$ 的成员。并且希望相对于真实数据概率分布损失也会小。

为此，只需确保 $$\mathcal{H}$$ 所有成员的经验风险都是其真实风险的良好近似。换句话说，我们需要假设类中的所有假设的经验风险一致地接近真实风险。

**定义4.1**：如果一个训练集 $$S$$ 被称为 $$\epsilon$$-**代表**，那么：
$$
\forall h \in \mathcal{H}, \ |L_S(h) - L_D(h)| \leq \epsilon.
$$
**推论4.2**：假设训练集 $$S$$ 是 $$\epsilon/2$$-代表，那么，任何 $$ERM_\mathcal{H}(S)$$ 的输出，即任何 $$h_S \in \arg \min_{h\in\mathcal{H}}L_S(h) $$ ，满足：
$$
L_\mathcal{D}(h_S) \leq \min_{h \in \mathcal{H}} L_\mathcal{D}(h) + \epsilon.
$$

> 证明：
> $$
> L_\mathcal{D}(h_S) \leq L_S(h_S) + \frac{\epsilon}{2} \leq L_S(h) + \frac{\epsilon}{2} \leq L_\mathcal{D}(h) + \frac{\epsilon}{2} + \frac{\epsilon}{2} = L_\mathcal{D}(h) + \epsilon
> $$
> 其中，第一个和第三个不等式是由于假设  $$S$$ 是 $$\epsilon/2$$-代表，第二个不等式成立是因为 $$h_S$$ 是一个ERM预测器。

这意味着，ERM规则是一个不可知PAC学习者，只要在训练集的随机选择中，以至少 $$1-\delta$$ 的概率，它将是一个 $$\epsilon$$-代表的训练集。一致收敛条件(uniform convergence condition)形式化了这一要求。

**定义4.3**：如果假设类 $$\mathcal{H}$$ 具有**一致收敛性质**，那么存在一个函数 $$m_{\mathcal{H}}^{\text{UC}} : (0,1)^2 \to \mathbb{N}$$，对于一个独立同分布样本集 $$S$$ 大小 $$m \geq m_{\mathcal{H}}^{\text{UC}}(\epsilon, \delta)$$，至少 $$1-\delta$$ 的概率，$$S$$ 将是一个 $$\epsilon$$-代表的训练集

> 简单点说，函数 $$m_{\mathcal{H}}^{\text{UC}}$$ 衡量获得一致收敛性质的（最小）样本复杂度，即需要多少例子才能确保样本以至少 $$1-\delta$$ 的概率是 $$\epsilon$$-代表的。“一致”代表这个固定的样本大小，适用于所有 $$\mathcal{H}$$ 的成员和域上的所有可能的概率分布。

**推论4.4**：如果一个类 $$\mathcal{H}$$ 具有一个函数 $$m_{\mathcal{H}}^{\text{UC}}$$ 的一致收敛性质，那么类是不可知PAC可学习的，并且样本复杂度 $$m_{\mathcal{H}}(\epsilon, \delta) \leq m_{\mathcal{H}}^{\text{UC}}(\epsilon/2, \delta)$$。此外，在这种情况下，$$\text{ERM}_\mathcal{H}$$ 范式是一个成功的不可知PAC学习算法。

（证明略）**推论4.6**：设 $$\mathcal{H}$$ 为一个有限假设类，那么它具有一致收敛性质，其样本复杂度为
$$
m_{\mathcal{H}}^{\text{UC}}(\epsilon, \delta) \leq \left\lceil \frac{\log(2|\mathcal{H}|/\delta)}{2\epsilon^2} \right\rceil
$$
同时，该类是不可知PAC可学习的，使用ERM算法，其样本复杂度为
$$
m_{\mathcal{H}}(\epsilon, \delta) \leq m_{\mathcal{H}}^{\text{UC}}(\epsilon/2, \delta) \leq \left\lceil \frac{2\log(2|\mathcal{H}|/\delta)}{\epsilon^2} \right\rceil.
$$

> 虽然上述推论仅适用于有限假设类，但有一个简单的技巧可以让我们很好地估计无限假设类的实际样本复杂度。考虑一个由 $$d$$ 个参数参数化的假设类。
>
> 举个例子，令 $$\mathcal{X}=\mathbb{R}, \mathcal{Y}=\{±1\}$$，假设类 $$\mathcal{H}$$ 为所有形式为 $$h_{\theta}(x)=\text{sign}(x-\theta)$$ 的函数。
>
> 也就是说，每个假设由一个参数 $$\theta\in \mathbb{R}$$ 参数化，对所有大于 $$\theta$$ 的实例输出1，反之输出-1。这是一个无限大小的假设类。然而，如果我们在实践中使用计算机学习这个假设类，我们可能会用浮点表示法维护真实数，假设使用64位表示。
>
> 因此，在实践中，我们的假设类由可以用64位浮点数表示的标量集参数化，64位数最多可以表示 $$2^{64}$$ 个数，也就有那么多假设类。$$d$$ 个数字就是 $$2^{64d}$$ 个假设类。至此我们将一个无限假设类变成了有限的，就可以套用推论4.6以及其他结论。