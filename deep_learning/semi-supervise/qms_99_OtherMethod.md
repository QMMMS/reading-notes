# Other SSL methods

## Entropy Minimization

由于半监督学习的样本过少，所以一种比较好的思路就是将网络在上一次产生的，自信程度比较高的预测（我们就当他是预测对了的）加入到本次的训练中。因此，在训练的时候我们需要让网络的预测更加自信，而不是比较犹豫，即熵最小化 Entropy Minimization

> 也可以看作阻止网络的决策边界在数据点附近

对于分类问题，网络最后必然是通过一个softmax来输出，而softmax是所有的类别经过归一化之后自信程度。假设网络对每一个类的自信程度都相近，那么整体的熵值就会越大，反之则越小。这个方法我们可以通过增加一个对于预测的损失项来实现（信息论熵的定义）：
$$
-\sum_{k = 1}^{C}f_{\theta}(x)_k \log f_{\theta}(x)_k
$$

## Label Smoothing

标签平滑是一种正则化技术，该技术应用于分类模型。主要动机是解决过度拟合并改善模型的鲁棒性、使模型对嘈杂或模棱两可的培训数据更加稳健。通过软化目标标签，鼓励模型对其预测的信心降低。

硬标签例如 [0,0,1,0] ，软化后的标签如 [ϵ,ϵ,1−(K−1)ϵ,ϵ]

具体来说，我们拿到 softmax 归一化的概率后
$$
q_i = \frac{\exp(z_i)}{\sum_{j = 1}^{K} \exp(z_j)}
$$
真实的概率分布有如下改变，其中，一共有 K 类，$$\varepsilon$$ 是一个较小的超参数：
$$
P_i=\begin{cases}
1, & \text{if }(i = y)\\
0, & \text{if }(i\neq y)
\end{cases}
\quad\Longrightarrow\quad
P_i=\begin{cases}
(1 - \varepsilon), & \text{if }(i = y)\\
\frac{\varepsilon}{K - 1}, & \text{if }(i\neq y)
\end{cases}
$$
交叉熵损失函数的改变如下：
$$
Loss = -\sum_{i = 1}^{K} p_i \log q_i \quad\Longrightarrow\quad Loss_i=\begin{cases}
(1 - \varepsilon) * Loss, & \text{if }(i = y)\\
\varepsilon * Loss, & \text{if }(i\neq y)
\end{cases}
$$
最优预测概率分布如下，其中α是任意实数：
$$
Z_i=\begin{cases}
+\infty, & \text{if }(i = y)\\
0, & \text{if }(i\neq y)
\end{cases}
\quad\Longrightarrow\quad
Z_i=\begin{cases}
\log\frac{(k - 1)(1 - \varepsilon)}{\varepsilon+\alpha}, & \text{if }(i = y)\\
\alpha, & \text{if }(i\neq y)
\end{cases}
$$
