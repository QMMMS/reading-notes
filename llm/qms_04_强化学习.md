# 强化学习与LLM

OpenAI 所做的报告《Reinforcement Learning from Human Feedback: Progress and Challenges》分享了强化学习在大语 言模型上的重要作用，可以概括为以下几个方面。

**强化学习比有监督学习更可以考虑整体影响**：有监督学习针对单个词元进行反馈，其目 标是要求模型针对给定的输入给出的确切答案。而强化学习是针对整个输出文本进行反馈，并不 针对特定的词元。这种反馈粒度的不同，使得强化学习更适合大语言模型，既可以兼顾表达多样 性，还可以增强对微小变化的敏感性。

自然语言十分灵活，可以用多种不同的方式表达相同的语 义。而有监督学习很难支持上述学习方式。强化学习则可以允许模型给出不同的多样性表达。

有监督微调通常采用交叉熵损失做为损失函数，由于总和规则，造成这种损失对个别 词元变化不敏感，如果改变个别的词元，只会对整体损失产生小的影响。但是，一个否定词可以 完全改变文本的整体含义。强化学习则可以通过奖励函数达到同时兼顾多样性和微小变化敏感性 两个方面。

**强化学习更容易解决幻觉问题**：用户在大语言模型时主要有三类输入：

- 文本型（TextGrounded）：用户输入相关文本和问题，让模型基于所提供的文本生成答案（例如，“本文中提到 的人名和地名有哪些”）；
- 求知型（Knowledge-Seeking）：用户仅提出问题，模型根据内在知识提供真实回答（例如，“流感的常见原因是什么”）；
- 创造型（Creative）：用户为提供问题或 说明，让模型进行创造性输出（例如，“写一个关于... 的故事”）。

有监督学习算法非常容易使得求 知型查询产生幻觉。在模型并不包含或者知道答案的情况下，有监督训练仍然会促使模型给出答案。而使用强化学习方法，则可以通过定制奖励函数，将正确答案赋予非常高的分数，放弃回答 的答案赋予中低分数，不正确的答案赋予非常高的负分，使得模型学会依赖内部知识选择放弃回 答，从而在一定程度上缓解模型幻觉问题。

**强化学习可以更好的解决多轮对话奖励累积问题**：多轮对话能力是大语言模型重要的基 础能力之一，多轮对话是否达成最终目标，需要考虑多次交互过程的整体情况，因此很难使用有 监督学习方法构建。而使用强化学习方法，可以通过构建奖励函数，将当前输出考虑整个对话的 背景和连贯性。

## PPO

LLM 的预训练要用到大量来自不同来源的语料库，而这本身就无法确保这些数据集的质量。此外，LLM 的主要目标是预测下一个 token，这个目标与「有用且安全地遵从用户指令」的目标并不一致。因此，LLM 可能会输出不真实、有害或对用户无用的内容。本质上讲，这些模型并未与用户意图对齐。**RLHF/PPO（Proximal Policy Optimization） 的主要目标是在各种任务上对齐语言模型与用户意图**，**其做法是使用人类反馈来微调模型**。

### 训练奖励模型

一般来说，强化学习是在监督微调之后进行的。PPO 算法需要一个预先训练好的奖励模型（reward model），该模型用于为大模型的输出打分，提供奖励信号。我们先从训练奖励模型讲起

训练奖励模型需要偏好数据，即针对同一个问题的两个答案的比较数据。其中，较好的回答称为 “chosen”，较差的回答称为 “rejected”。奖励模型最终需要能够针对一个问答序列给出明确的得分。

> 由于在强化学习中，奖励信号至关重要，它决定了模型的改进方向，因此通常会采用与当前大模型能力相近或者更强的大模型来训练奖励模型。虽然这些模型与当前大模型能力相当，但评价一个回答的好坏往往比生成一个好的回答更容易，而且随着模型输出能力的提升，其评价能力也会相应提高。不过，大模型的能力极限是由预训练阶段决定的，强化学习只能让模型的能力尽可能逼近这个极限

**如何把大模型改造成奖励模型**？对于标准大模型，每个 token 在输出层会经过 llm head 层，该层输入维度是 token 的 hidden size，输出维度是字典的维度，且其参数为所有 token 共享。

当把大模型改造成奖励模型时，输入是问题和回答的拼接；输出需要一个 score head，其输入维度同样是 token 的 hidden size，但输出维度只有一位，并且只对序列的最后一个 token 调用 score head，因为只有最后一个 token 能看到前面所有序列，从而对整个序列进行评分，得到问答对的奖励

给定一个 prompt 和我们模型的参数 θ，令模型预测“人类会选择 chosen 回答而不是 rejected 回答”的概率为：
$$
P(\text{chosen} \succ \text{rejected}|\text{prompt}, \theta) = \text{sigmoid}(\text{score}_{\text{chosen}} - \text{score}_{\text{rejected}})
$$
极大似然估计的目标是最大化所有观测数据出现的联合概率（我们已经知道了结果，现在希望模型能尽可能接近这些结果）。假设我们有 N 个独立的偏好数据对，那么总的**似然函数 (Likelihood)** 就是所有这些概率的连乘积：
$$
\begin{align}
\mathcal{L}(\theta)&=\prod\limits_{i=1}^{N}P(\text{chosen}_{i}\succ\text{rejected}_{i}\mid\text{prompt}_{i},\theta)\\
&=\prod\limits_{i=1}^{N}\text{sigmoid}(\text{score}_{\text{chosen}_{i}}-\text{score}_{\text{rejected}_{i}})
\end{align}
$$
我们取对数似然 (Log-Likelihood)，目标是**最大化**这个对数似然函数。在机器学习中，我们习惯于**最小化**一个**损失函数 (Loss Function)**。这很简单，只需要在对数似然前面加一个负号就行了。
$$
Loss(\theta)=-\sum_{i=1}^{N}\log(\operatorname{sigmoid}(score_{\text{chosen}_{i}}-score_{\text{rejected}_{i}}))
$$
看一下利用 hugging face 的[简单实现](https://github.com/RethinkFun/trian_ppo/blob/main/train_ppo/train_reward.py)，数据每条包含 “Question”“Chosen”“Rejected” 三部分。

```text
{"question":"什么是数据库？", "chosen":"数据库是一个有组织的数据集合，允许高效的数据存储、检索和管理。","rejected":"数据库用于存储数据。"}
```

训练代码如下：首先定义 tokenizer 和模型，以量化模型方式加载

```python
model_path = r'D:\work\models\Meta-Llama-3.1-8B-Instruct'
tokenizer = AutoTokenizer.from_pretrained(model_path, use_fast=False)
tokenizer.padding_side = "right"
tokenizer.pad_token = tokenizer.eos_token
bnb_config = BitsAndBytesConfig(
    load_in_4bit=True,  # 量化
    bnb_4bit_use_double_quant=True,
    bnb_4bit_quant_type="nf4",
    bnb_4bit_compute_dtype=torch.float16
)
# 模型类型为序列分类模型 AutoModelForSequenceClassification
# 分类为 1 时即回归模型，可输出单个连续值
model = AutoModelForSequenceClassification.from_pretrained(model_path,
                                                           num_labels=1,
                                                           quantization_config=bnb_config)
model.config.pad_token_id = tokenizer.pad_token_id
```

定义 LoRA 配置，得到 LoRA 模型

```python
peft_config = LoraConfig(
    r=8,
    target_modules=["q_proj",
                    "v_proj",
                    "k_proj",
                    "o_proj",
                    "gate_proj",
                    "down_proj",
                    "up_proj"
                    ],
    task_type=TaskType.SEQ_CLS,
    lora_alpha=16,
    lora_dropout=0.05
)
model = prepare_model_for_kbit_training(model)
model = get_peft_model(model, peft_config)
```

接着加载偏好数据，对数据进行处理

```python
def process_func(example):
    # 将问题和回答拼接
    chosen = example["question"] + example["chosen"]
    rejected = example["question"] + example["rejected"]

    tokenized_chosen = tokenizer(chosen)  # 分词
    tokenized_rejected = tokenizer(rejected)

    new_example = {}
    new_example["input_ids_chosen"] = tokenized_chosen["input_ids"]
    new_example["attention_mask_chosen"] = tokenized_chosen["attention_mask"]
    new_example["input_ids_rejected"] = tokenized_rejected["input_ids"]
    new_example["attention_mask_rejected"] = tokenized_rejected["attention_mask"]
    return new_example

dataset = dataset.map(process_func, remove_columns=['question', 'chosen', 'rejected'])
```

然后定义训练奖励模型的配置（可指定模型输出位置、训练轮数、每个 GPU 上的 batch size 等）

```python
config = RewardConfig(output_dir="./reward_model")
config.num_train_epochs = 1
config.per_device_train_batch_size = 1
```

最后定义一个 reward trainer，传入模型、tokenizer、reward config 和训练数据集，调用 trainer.train () 进行训练

```python
trainer = RewardTrainer(
    model=model,
    tokenizer=tokenizer,
    args=config,
    train_dataset=dataset
)
trainer.train()
```

### PPO 涉及的模型

PPO 训练需要四个模型：

![](./img/ppo1.png)

1. **基准模型**：通常是经过监督微调后的大模型，作为基准，新训练的模型输出的概率分布不能与它相差太大。其输出通过 llm head，输入维度是 token 的 hidden size，输出是字典维度，然后根据概率抽样得到输出 token。
2. **训练的模型**：结构与基准模型完全一致，PPO 训练的目标就是优化该模型，同时要保证其输出的概率分布与基准模型相差不大。
3. **奖励模型**：对一个问答序列进行评分，输出一个分数。其输出通过一个 score head，输入维度是 token 的 hidden size，输出维度为 1，对问答对序列的最后一个 token 的输出通过 score head 计算后得到该问答序列的得分。
4. **状态价值模型**：对每个状态评估其价值，即根据截止到目前的 token 序列，预测到序列生成结束后该问答序列的期望回报。其输出通过一个 value head，输入维度是 token 的 hidden size，输出维度为 1，每个输出的 token 都共享这个 value head 的权重。

为减少显存占用，可采用只加载一个大模型和多个 adapter 的技术，并且将训练的模型和状态价值模型合并，共用一套 LoRA 参数，使其同时拥有 llm head 和 value head

![](./img/ppo2.png)

回顾一下强化学习概念，对于大模型输出的每一步，state 是截止到当前 token 的序列，action 是接下来输出的 token。奖励模型只针对完整输出给出一个得分，其他 token 的 score 为零。

我们可以为每个 token 增加一个奖励项，使其与输出的概率分布和基准模型之间的 KL 散度相关。训练模型做出每个 action（输出每个 token）的 reward 等于其输出的概率分布相对于基准模型输出的概率分布的 KL 散度乘以 -0.2（调整系数），再加上 score 的值。

![](./img/ppo3.png)

我们定义训练的损失函数，我们现在在训练两个模型

- 文本输出大模型
- 输出每个token状态价值的模型

### 训练状态价值模型

我们先看状态价值模型的 Loss，首先需要知道 label 是什么，有三种生成方式：

1. **蒙特卡洛法**：将整个问答序列视为一次随机采样，统计当前 token 后面序列的奖励的衰减累积值作为 label，但 label 值的方差很大。
2. **时序差分法**：只采样一步，当前步状态的价值函数等于采样一步得到的奖励加上衰减因子乘以下一步的状态价值，可减少 label 的方差，但依赖于当前状态价值网络的估计，会带来较大偏差。
3. **广义优势法**：即之前讲 PPO 算法时提到的 GAE 优势函数加上当前步的状态价值估计值。GAE 优势函数表示每一步状态做出当前动作的期望回报减去当前状态的期望回报，所以 GAE 加上当前步的状态价值就等于当前步采样当前动作的期望回报，它平衡了方差和偏差。

三种方法的公式分别如下
$$
\begin{align}
V_{label}(s_t)&=r_t+\gamma r_{t + 1}+\gamma^2 r_{t + 2}+\ldots+\gamma^{T - t}r_T\\
V_{label}(s_t)&=r_t+\gamma V(s_{t + 1})\\
V_{label}(s_t)&=A_t^{GAE}+V(s_t)
\end{align}
$$

> 回顾一下 GAE 优势函数的计算公式：
> $$
> \begin{align}
> &\delta_{t}^{V}=r_{t}+\gamma * V_{\theta}(s_{t + 1})-V_{\theta}(s_{t})\\
> &A_{\theta}^{GAE}(s_{t},a)=\sum_{b = 0}^{\infty}(\gamma\lambda)^{b}\delta_{t + b}^{V}
> \end{align}
> $$
> 我们将第二个公式改写为更加适合编程计算的样式，并实现出来
> $$
> A_{\theta}^{GAE}(s_{t},a)=\delta_{t}^{V}+\gamma\lambda A_{\theta}^{GAE}(s_{t + 1},a)
> $$
>
> ```python
> for t in reversed(range(gen_len)):  # 从后向前计算
>     nextvalues = values[:, t + 1] if t < gen_len - 1 else 0.0
>     delta = rewards[:, t] + self.config.gamma * nextvalues - values[:, t]
>     # 当前步的 delta，加上 gamma 乘 lambda 乘 下一步的 gae
>     lastgaelam = delta + self.config.gamma * self.config.lam * lastgaelam
>     advantages_reversed.append(lastgaelam)
> advantages = torch.stack(advantages_reversed[::-1]).transpose(0, 1)
> ```
>
> Hugging Face 库采用广义优势法计算状态价值网络的 label 值：
>
> ```python
> returns = advantages + values  # 每一步的期望回报，label
> vpredclipped = clip_by_value(
>     vpreds,
>     values - self.config.cliprange_value,
>     values + self.config.cliprange_value,
> )
> vf_losses1 = (vpreds - returns) ** 2
> vf_losses2 = (vpredclipped - returns) ** 2 
> # 为使训练稳定，引入 clip 值，限制预测状态价值与重要性采样网络预测的状态价值的变化范围
> vf_loss = 0.5 * masked_mean(torch.max(vf_losses1, vf_losses2), mask)
> # 乘以 0.5 为了求导时与平方项的 2 约掉
> ```

### PPO 的 Loss

> 复习一下之前讲解的 PPO 算法的损失公式
> $$
> Loss_{ppo}=-\frac{1}{N}\sum_{n = 1}^{N}\sum_{t = 1}^{T_{n}}A_{\theta'}^{GAE}(s_{n}^{t},a_{n}^{t})\frac{P_{\theta}(a_{n}^{t}|s_{n}^{t})}{P_{\theta'}(a_{n}^{t}|s_{n}^{t})}+\beta KL(P_{\theta},P_{\theta'})\\
> $$

实际代码实现与之前讲解的 PPO 算法的损失公式有两点不同：

- 进行重要性采样的模型可以和参考模型不一样；
-  KL 散度已在 reward 中体现，可去掉损失函数里关于 KL 的项。

$$
Loss_{ppo}=-\frac{1}{N}\sum_{n = 1}^{N}\sum_{t = 1}^{T_{n}}A_{\theta''}^{GAE}(s_{n}^{t},a_{n}^{t})\frac{P_{\theta}(a_{n}^{t}|s_{n}^{t})}{P_{\theta''}(a_{n}^{t}|s_{n}^{t})}
$$

- θ 表示正在训练的网络模型
- θ' 是基准模型，训练的模型输出概率分布不能和基准模型相差太大
- θ'' 是进行重要性采样的模型，会在训练过程中逐步更新，保持与训练模型相差不大，在一些实践中，重要性采样的模型和训练的网络模型是同一个

来看一下实现

```python
ratio = torch.exp(logprobs - old_logprobs)  # 训练网络与重要性采样网络输出概率的比值
pg_losses = -advantages * ratio
pg_losses2 = -advantages * torch.clamp(ratio, 1.0 - self.config.cliprange, 1.0 + self.config.cliprange)  # 为保证训练稳定，对概率比值进行裁剪
pg_loss = masked_mean(torch.max(pg_losses, pg_losses2), mask)

# 总的loss包含PPO loss和State Value的Loss
loss = pg_loss + self.config.vf_coef * vf_loss  
```

### PPO 训练伪代码

```python
# 从 prompt 数据集里取出一个 batch 的 prompt 数据
for batch_prompt in prompt_dataset:
    batch_response = active_model.generate(batch_prompt)  # 利用重要性采样网络（即当前训练网络）生成回答
    batch_data = concat(batch_prompt, batch_response)  # 问题和回答合并生成训练文本
    batch_scores = reward_model(batch_data)  # 用奖励模型对训练文本打分

    # 针对整个字典所有 token 的概率分布、作为输出 token 的概率、每个 token 的状态价值
    batch_all_probs, batch_probs, batch_all_values = active_model.forward_pass(batch_data)
    ref_all_probs, ref_probs, ref_all_values = ref_model.forward_pass(batch_data)
    kls = compute_KL(batch_all_probs, ref_all_probs)
    rewards = compute_rewards(batch_scores, kls)
    advantages = compute_advantages(batch_all_values, rewards)
    # return 的值等于 advantage 的值加上重要性采样网络输出的状态价值
    returns = advantages + batch_all_values

    for i in range(epoch):  # 对于一个 batch 的数据，要训练 epochs 次，
        active_all_probs, active_probs, active_all_values = active_model.forward_pass(batch_data)

        # 状态价值网络的 loss
        loss_state_value = torch.mean((returns - active_all_values) ** 2)
        # 训练网络和重要性采样网络在每个 token 的概率比值
        ratio = active_probs / batch_probs
        # 比值乘以负的 advantage 得到 PPO loss
        loss_ppo = torch.mean(-advantages * ratio)
        # 最终的 loss 是状态价值网络的 loss 加上 PPO loss
        loss = loss_ppo + value_loss_rate * loss_state_value
        loss.backward()
        optimizer.step()
        optimizer.zero_grad()
```

实际上不需要写这么多代码，我们看看使用 Hugging Face 库[训练demo](https://github.com/RethinkFun/trian_ppo/blob/main/train_ppo/train_ppo.py)中的核心部分

```python
for batch in ppo_trainer.dataloader:
    query_tensors = batch  # batch 数据只有问题，没有回答

    response_tensors = ppo_trainer.generate(  # 生成回答
        query_tensors, return_prompt=False,  **generation_kwargs)
    
    # reward 模型打分
    scores = []
    for query, response in zip(query_tensors, response_tensors):
        input_ids = torch.concat([query, response], dim=0)
        input_ids = torch.unsqueeze(input_ids, dim=0)
        score = ppo_trainer.model.compute_reward_score(input_ids=input_ids)[0, -1, 0]
        scores.append(score)
        
    # 传入问题、回答、得分，进行训练
    stats = ppo_trainer.step(query_tensors, response_tensors, scores)
```

## DPO

### 介绍

DPO（Direct Preference Optimization， 直接偏好优化）通过利用奖励函数与最优策略之间的映射关系，证明这个受限的奖励最大化问题可以通过单阶段的策略训练来精确优化，本质上是在人类偏好数据上解决一个分类问题。

它的工作原理是创建人类偏好对的数据集，每个偏好对都包含一个提示和两种可能的完成方式——一种是首选，一种是不受欢迎。然后对LLM进行微调，以最大限度地提高生成首选完成的可能性，并最大限度地减少生成不受欢迎的完成的可能性。

DPO是稳定的、性能和计算成本轻量级的，无需拟合奖励模型，在微调期间从 LM 中采样，或执行显着的超参数调整。通过实验表明：DPO 进行微调超过了 RLHF 效果，并提高了摘要和单轮对话的响应质量。

传统的RLHF(奖励模型+PPO)步骤为：

1. 预训练的基础LLM
2. 监督微调（SFT）LLM
3. 奖励模型（LLM，但修改为奖励模型）
4. PPO优化的语言模型（最终与偏好对齐的LLM）

DPO通过完全移除奖励模型来简化这个过程：

1. 预训练的基础LLM
2. 监督微调（SFT）LLM
3. DPO优化的语言模型（最终与偏好对齐的LLM）

### Bradley -Terry模型

Bradley-Terry模型是对比较关系进行建模，例如下面这个例子，已知下表信息，问 B 战胜 C 的概率有多大：

| 对战   | 胜   | 负   |
| ------ | ---- | ---- |
| A 对 B | 8    | 4    |
| A 对 C | 3    | 5    |

Bradley Terry模型假设每个元素都有一个隐含的实例参数。用 $$\alpha_i$$ （大于0）来表示，元素 i 战胜元素 j 的概率可以如下表示：
$$
P(i \succ j)=\frac{\alpha_{i}}{\alpha_{i}+\alpha_{j}}
$$
对于 B 战胜 C 的概率，可以用对数最大似然估计法来进行求解，因为我们已经知道了两场对战结果，所以我们求隐含的实例参数来使这种对战结果的概率最大

> 公式推导过程，总的联合概率是每个事件的概率连乘，对于 A 对 B 战胜 8 次，就连乘 8 次，然后取 ln，变成对数最大似然估计

$$
\ln L=8\ln \left(\frac{\alpha_{A}}{\alpha_{A}+\alpha_{B}}\right)+4\ln \left(\frac{\alpha_{B}}{\alpha_{A}+\alpha_{B}}\right)+3\ln \left(\frac{\alpha_{A}}{\alpha_{A}+\alpha_{C}}\right)+5\ln \left(\frac{\alpha_{C}}{\alpha_{A}+\alpha_{C}}\right)
$$

假设 $$\alpha_{A}=1$$，那么 $$\alpha_{B}=1/2, \alpha_{C}=5/3$$，最后得到 B 战胜 C 的概率为 0.23

如果我们不想对 $$\alpha$$ 进行直接求导来求似然最大值，我们也可以通过优化器对它进行迭代优化来进行求解。一般的 loss 函数为：
$$
\text{Loss}=-\mathbb{E}_{\left(\alpha_{x},\alpha_{y}\right)\sim D}\left[\ln\frac{\alpha_{x}}{\alpha_{x}+\alpha_{y}}\right]
$$
在这个一般化的公式中，相当于我们已知 x 战胜了 y，现在我们来极大似然，最后加一个负号成为损失函数，这与分类问题的交叉熵损失函数是一致的。

### DPO loss

在强化学习里面，令大模型输入的 prompt 是 x，回答是y。回答y的好坏需要靠reward模型来进行评估。reward function有可能返回负数，我们对reward函数外部再加一个指数函数来让它变成正数。
$$
P\left(y_{1} \succ y_{2}\right)=\frac{\exp\left(r\left(x, y_{1}\right)\right)}{\exp\left(r\left(x, y_{1}\right)\right)+\exp\left(r\left(x, y_{2}\right)\right)}
$$
然后我们通过引入 sigmoid 函数 $$\sigma$$ 来简化损失，注意，DPO 其实是用不到 reward 模型的，我们后面会通过公式推导处理掉：
$$
\begin{align}
\text{Loss}&=-\mathbb{E}_{(x,y_{w},y_{l})\sim D}\left[\ln\frac{\exp(r(x,y_{w}))}{\exp(r(x,y_{w}))+\exp(r(x,y_{l}))}\right]\\
&= -\ln\sigma\left(r\left(x, y_{w}\right)-r\left(x, y_{l}\right)\right)
\end{align}
$$
DPO 的训练目标如下，其中 $$\pi_{ref}(y|x)$$ 为基准模型（一般为SFT之后），$$\pi(y|x)$$ 为我们训练的模型：
$$
\max_{\pi}\mathbb{E}_{x\sim D,y\sim\pi}[r(x,y)]-\beta\mathbb{D}_{KL}[\pi(y|x)||\pi_{ref}(y|x)]
$$
我们可以把这个公式看作两部分：第一部分尽可能拿到更多的奖励，第二部分是一个正则项不能偏离原来的模型太远，$$\beta$$ 越大则越与原模型一致

在将其化简后，我们的训练目标等价为：
$$
\min _{\pi}\mathbb{E}_{x\sim D}\left[\mathbb{D}_{K L}\left(\pi(y\mid x)||\pi^{*}(y\mid x)\right)\right] \\
$$

$$
\frac{\pi_{ref}(y|x)\exp\left(\frac{1}{\beta}r(x,y)\right)}{\sum_{y}\pi_{ref}(y|x)\exp\left(\frac{1}{\beta}r(x,y)\right)}=\pi^{*}(y|x)
$$

这个 KL 散度取最小值0时，即 $$\pi(y|x)$$ 与 $$\pi^{*}(y|x)$$ 一致，那么通过建立这个等式，我们继续化简之前的 Loss 函数，这样我们就去掉了奖励模型
$$
\begin{align}
\text{Loss}
&= -\ln\sigma\left(r\left(x, y_{w}\right)-r\left(x, y_{l}\right)\right)\\
&= -\ln \sigma \left( \beta \ln \frac{\pi(y_w \mid x)}{\pi_{ref}(y_w \mid x)} - \beta \ln \frac{\pi(y_l \mid x)}{\pi_{ref}(y_l \mid x)} \right)
\end{align}
$$

## 总体介绍

### **1. PPO (Proximal Policy Optimization)**

**核心标签：** 经典基石 / 稳定性之王 / RL入门必修

- **一句话介绍：**虽然是2017年提出的经典算法，但在2025年依然是许多通用任务的默认首选。它就像是自动驾驶里的“定速巡航”，不求最快，但求最稳，保证训练过程不崩溃。
- **通俗原理：**想象你在教AI骑自行车。传统的强化学习可能因为一次摔倒就彻底不敢骑了（策略更新步幅过大）。PPO通过一个“裁剪（Clip）”机制，强制AI每次只能微调自己的动作习惯，不能大幅度修改。这种“小步快跑”的策略，保证了学习过程的下限，极大地减少了训练失败的概率。
- **优点：**
- **极度稳定：** 对超参数不敏感，不需要复杂的调参就能跑通。
- **通用性强：** 从机器人控制到早期的RLHF（如ChatGPT早期版本），适用范围极广。
- **缺点：**
- **内存占用高：** 需要同时维护策略网络（Actor）和价值网络（Critic）。
- **在大模型时代略显笨重：** 面对千亿参数的LLM，PPO的显存消耗和计算效率逐渐成为瓶颈。
- **2025现状：**依然是中小型模型和非LLM控制任务的霸主，但在大规模语言模型训练中逐渐被GRPO等更轻量级算法取代。

### **2. GRPO (Group Relative Policy Optimization)**

**核心标签：** DeepSeek同款 / 显存优化 / 高效推理

- **一句话介绍：**DeepSeek-R1背后的核心算法。它摒弃了庞大的“裁判员（Critic模型）”，通过组内对比，用更少的显存训练出逻辑推理能力更强的模型。
- **通俗原理：**PPO需要一个专门的“老师”模型来打分（Critic），这非常占用显存。GRPO的做法是：给同一个题目，让AI生成一组（比如8个）不同的答案。然后把这组答案放在一起比较，**比平均水平好的给予奖励，比平均水平差的给予惩罚**。这种“组内相对排名”的方法，不需要额外的模型参数，直接节省了约一半的显存资源。
- **优点：**
- **显著节省显存：** 移除了Critic模型，同样的硬件条件下能训练参数量更大的模型。
- **无需训练价值函数：** 简化了训练流程，避免了因Critic拟合不佳导致的训练震荡。
- **缺点：**
- **依赖采样多样性：** 如果生成的答案高度趋同，缺乏对比度，训练效果会大打折扣。
- **2025现状：**大语言模型（特别是推理类模型）训练的主流选择，是个人开发者和中小实验室复现SOTA效果的核心工具。

### **3. GSPO (Group Sequence Policy Optimization)**

**核心标签：** 序列级优化 / 长文本利器 / MoE模型适配

- **一句话介绍：**针对GRPO的进阶优化版。它不再局限于关注单个Token的优劣，而是强调文本整体序列的流畅度，特别适合训练MoE（混合专家）架构的超大模型。
- **通俗原理：**之前的算法（如GRPO）有时会过于微观地关注某个词用得是否准确。GSPO认为，文本生成应看重整体逻辑（Sequence-level）。它通过一种新的数学加权方法，根据整个序列生成的概率来动态调整学习力度。这就像修改作文，不是盯着错别字改，而是着重调整段落结构和整体逻辑。
- **优点：**
- **方差更小，训练更稳：** 解决了GRPO在某些极端分布下的不稳定性。
- **对MoE模型极其友好：** 完美适配2025年主流的混合专家模型架构（如Qwen3等）。
- **缺点：**
- **实现稍复杂：** 数学推导和代码实现相比GRPO更为繁琐。
- **2025现状：**正在成为追求极致性能的头部大厂的新宠，特别是在长文本生成和复杂逻辑任务上表现优异。

### **4. DAPO (Decoupled Clip and Dynamic Sampling)**

**核心标签：** 工业级优化 / 动态采样 / 大规模训练系统

- **一句话介绍：**它是GRPO的“工业化改良版”。通过解耦裁剪机制和动态数据采样，专治大模型训练中的“偷懒”和“死记硬背”问题。
- **通俗原理：**大模型训练容易出现两个极端：要么这一批数据太简单，AI全做对了学不到东西；要么为了防止改动太大，把有用的更新也给限制了。DAPO主要做了两点改进：

1. **Clip-Higher：** 允许AI在置信度高的方向上适当增大更新步幅。
2. **动态采样：** 实时监控训练数据，自动过滤掉太简单的题（全对）和太难的题（全错），只保留那些位于“最近发展区”的样本，最大化训练效率。

- **优点：**
- **训练效率极高：** 避免无效计算，将算力集中在有效样本上。
- **工程属性强：** 依托于verl等开源框架，非常适合工程落地。
- **缺点：**
- **对数据管道要求高：** 需要具备动态筛选数据的能力，对底层架构有一定要求。
- **2025现状：**工程落地首选，特别是当算力资源有限（如仅有少量GPU集群）但需要冲击数学竞赛等高难度榜单时。

### **5. BAPO (Balanced Policy Optimization)**

**核心标签：** Off-Policy / 平衡机制 / 旧数据利用

- **一句话介绍：**它解决了强化学习中的“数据利用率”问题。即便利用历史旧策略产生的数据（Off-Policy），也能通过动态平衡机制，保证模型学得又快又好。
- **通俗原理：**在训练中，负面反馈往往比正面反馈多，这会导致模型变得保守，输出的多样性（熵）下降。BAPO引入了一种**自适应裁剪机制**，动态调整对正面样本和负面样本的接纳程度，强行平衡两者的影响力，从而保护了模型的探索欲望和创造力。
- **优点：**
- **样本效率高：** 能高效利用旧策略数据，大幅提升数据性价比。
- **防止模型坍塌：** 有效缓解了RL训练中常见的熵崩塌（模型只会输出重复内容）问题。
- **缺点：**
- **超参调节：** 引入了新的平衡参数，需要一定的调试经验。
- **2025现状：**在需要频繁利用历史数据进行离线强化学习的场景中表现卓越。

### **6. ARPO (Agentic Reinforced Policy Optimization)**

**核心标签：** Agent专用 / 工具调用 / 多轮对话

- **一句话介绍：**专门为**AI Agent（智能体）**设计的算法。它不仅优化AI的语言生成，更专注于优化AI在多轮对话中对工具（搜索、代码解释器等）的调用策略。
- **通俗原理：**普通的RL算法通常将整个对话视为一个整体进行奖励。但在Agent场景下，AI可能第一步选错工具，导致后续步骤无效。ARPO通过监测熵值，识别出AI**“犹豫不决”的关键步骤（如调用工具前）**，并在这些关键节点强制进行多次试错采样（Branch Sampling），重点突破难点，而非盲目地从头生成到尾。
- **优点：**
- **Agent能力特化：** 在工具调用（Tool Use）和复杂推理任务上优于传统算法。
- **节省Token：** 相比于GRPO的全程多次采样，ARPO只在关键节点多次采样，大幅降低Token消耗。
- **缺点：**
- **场景受限：** 专门针对多轮推理和工具调用场景，纯文本聊天任务收益有限。
- **2025现状：**构建复杂AI Agent系统（如自动写代码、自动科研助手）的首选算法。
