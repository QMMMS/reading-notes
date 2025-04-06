《**Think Twice: Enhancing LLM Reasoning by Scaling Multi-round Test-time Thinking**》(https://arxiv.org/pdf/2503.19855) 利用先前的答案作为后续轮次的提示，迭代完善模型推理，关键提示为:

```
{原问题提示}助手之前的回答是:{Last Round Answer}，请重新回答
```

在QWQ-32B和DeepSeek-R1等多个模型上进行的广泛实验显示，在AIME 2024、MATH-500等各种基准测试中，性能持续提高。例如，QWQ-32b在AIME 2024数据集上的准确率从80.3%(第一轮)提高到了82.1%(第二轮)，而DeepSeek-R1的准确率也从79.7%提高到了82.0%。

> 现在单次think大家体感下来就已经很慢了，再加一次思考，会增加时间，落地意义不是很大？并且跟这个方向上有个相反的方向，就是做think时间的缩短

---

《Long Is More Important Than Difficult for Training Reasoning Models》(https://arxiv.org/pdf/2503.18069) ，通过实验发现，影响训练模型性能的主要是推理长度而不是问题难度；确定推理长度的缩放规律，表明模型性能随着推理数据长度的增长而以对数线性方式增长。

通过对Long1K数据集上的Qwen2.5-32B指令语言模型进行微调后，提出Long1K-32B，仅使用1000个训练样本，数学准确率达到95.6%，GPQA准确率达到71.1%，优于DeepSeek-R1-Distil-QWEN-32B。


