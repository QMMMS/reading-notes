import numpy as np
import planar_utils


def layer_sizes(X, Y):
    """
    确定神经网络的结构

    :param X: 输入数据集,维度为（特征数量，样本数量）
    :param Y: 标签，维度为（输出的数量，样本数量）
    :return:
        n_x - 输入层的数量
        n_y - 输出层的数量
    """
    n_x = X.shape[0]  # 输入层
    n_y = Y.shape[0]  # 输出层

    return n_x, n_y


def initialize_parameters(n_x, n_h, n_y):
    """
    初始化参数

    :param n_x: 输入层节点的数量
    :param n_h: 隐藏层节点的数量
    :param n_y: 输出层节点的数量
    :return: parameters 包含参数的字典：
            W1 - 权重矩阵,维度为（n_h，n_x）
            b1 - 偏向量，维度为（n_h，1）
            W2 - 权重矩阵，维度为（n_y，n_h）
            b2 - 偏向量，维度为（n_y，1）
    """
    W1 = np.random.randn(n_h, n_x) * 0.001
    b1 = np.zeros(shape=(n_h, 1))
    W2 = np.random.randn(n_y, n_h) * 0.001
    b2 = np.zeros(shape=(n_y, 1))

    # 使用断言确保我的数据格式是正确的
    assert (W1.shape == (n_h, n_x))
    assert (b1.shape == (n_h, 1))
    assert (W2.shape == (n_y, n_h))
    assert (b2.shape == (n_y, 1))

    parameters = {"W1": W1,
                  "b1": b1,
                  "W2": W2,
                  "b2": b2}

    return parameters


def forward_propagation(X, parameters):
    """
    对所有样本进行一次正向传播

    :param X: 输入数据集,维度为（特征数量，样本数量）
    :param parameters: 包含参数 W1, b1, W2, b2 的字典
    :return: cache 包含 Z1, A1, Z2, A2的字典
    """
    W1 = parameters["W1"]
    b1 = parameters["b1"]
    W2 = parameters["W2"]
    b2 = parameters["b2"]
    # 前向传播计算A2
    Z1 = np.dot(W1, X) + b1
    A1 = np.tanh(Z1)
    Z2 = np.dot(W2, A1) + b2
    A2 = planar_utils.sigmoid(Z2)
    # 使用断言确保我的数据格式是正确的
    assert (A2.shape == (1, X.shape[1]))
    cache = {"Z1": Z1,
             "A1": A1,
             "Z2": Z2,
             "A2": A2}

    return A2, cache


def compute_cost(A2, Y):
    """
    计算交叉熵成本 (J)

    :param A2: 预测的输出值
    :param Y: 标签向量,维度为（1，样本数量）
    :return: cost 交叉熵成本 (J)
    """
    m = Y.shape[1]

    logprobs = np.multiply(np.log(A2), Y) + np.multiply((1 - Y), np.log(1 - A2 + 1e-5))
    # RuntimeWarning: divide by zero encountered in log错误解决
    cost = - np.sum(logprobs) / m
    cost = float(np.squeeze(cost))

    assert (isinstance(cost, float))

    return cost


def backward_propagation(parameters, cache, X, Y):
    """
    搭建反向传播函数

    :param parameters: 包含参数 W1, b1, W2, b2 的字典
    :param cache: 包含 Z1, A1, Z2, A2的字典
    :param X: 输入数据，维度为（2，数量）
    :param Y: 标签，维度为（1，样本数量）
    :return: grads 包含dW1, db1, dW2, db2 的字典
    """
    m = X.shape[1]

    W2 = parameters["W2"]
    A1 = cache["A1"]
    A2 = cache["A2"]

    dZ2 = A2 - Y
    dW2 = (1 / m) * np.dot(dZ2, A1.T)
    db2 = (1 / m) * np.sum(dZ2, axis=1, keepdims=True)
    dZ1 = np.multiply(np.dot(W2.T, dZ2), 1 - np.power(A1, 2))
    dW1 = (1 / m) * np.dot(dZ1, X.T)
    db1 = (1 / m) * np.sum(dZ1, axis=1, keepdims=True)
    grads = {"dW1": dW1,
             "db1": db1,
             "dW2": dW2,
             "db2": db2}

    return grads


def update_parameters(parameters, grads, learning_rate=1.2):
    """
    更新规则更新参数

    :param parameters: 包含参数 W1, b1, W2, b2 的字典
    :param grads: grads 包含dW1, db1, dW2, db2 的字典
    :param learning_rate: 学习速率
    :return: parameters - 包含更新参数 W1, b1, W2, b2 的字典
    """
    W1, W2 = parameters["W1"], parameters["W2"]
    b1, b2 = parameters["b1"], parameters["b2"]

    dW1, dW2 = grads["dW1"], grads["dW2"]
    db1, db2 = grads["db1"], grads["db2"]

    W1 = W1 - learning_rate * dW1
    b1 = b1 - learning_rate * db1
    W2 = W2 - learning_rate * dW2
    b2 = b2 - learning_rate * db2

    parameters = {"W1": W1,
                  "b1": b1,
                  "W2": W2,
                  "b2": b2}

    return parameters


def model(X, Y, n_h, num_iterations, learning_rate=0.5, print_cost=False):
    """
    封装好的双层神经网络模型

    :param X: 输入数据集,维度为（特征数量，样本数量）
    :param Y: 标签，维度为（输出的数量，样本数量）
    :param n_h: 隐藏层的数量
    :param num_iterations: 梯度下降循环中的迭代次数
    :param learning_rate: 学习速率
    :param print_cost: 如果为True，则每1000次迭代打印一次成本数值
    :return: parameters  模型学习的参数，它们可以用来进行预测
    """
    n_x = layer_sizes(X, Y)[0]
    n_y = layer_sizes(X, Y)[1]
    parameters = initialize_parameters(n_x, n_h, n_y)  # 初始化

    for i in range(num_iterations):
        A2, cache = forward_propagation(X, parameters)
        cost = compute_cost(A2, Y)
        grads = backward_propagation(parameters, cache, X, Y)
        parameters = update_parameters(parameters, grads, learning_rate)

        if print_cost and i % 1000 == 0:
            print("第 ", i, " 次循环，成本为：" + str(cost))
    return parameters


def predict(parameters, X):
    """
    使用学习的参数预测

    :param parameters: 包含参数的字典类型的变量
    :param X: 输入数据集,维度为（特征数量，样本数量）
    :return: predictions 模型预测的向量（红色：0 /蓝色：1）
    """
    A2, cache = forward_propagation(X, parameters)
    predictions = np.round(A2)

    return predictions


if __name__ == '__main__':
    X, Y = planar_utils.load_planar_dataset()

    print("测试layer_sizes")
    n_x, n_y = layer_sizes(X, Y)
    print("输入层的节点数量为: n_x = " + str(n_x))
    print("输出层的节点数量为: n_y = " + str(n_y))
    print()

    print("测试initialize_parameters")
    parameters = initialize_parameters(n_x, 4, n_y)
    print("W1 = " + str(parameters["W1"]))
    print("b1 = " + str(parameters["b1"]))
    print("W2 = " + str(parameters["W2"]))
    print("b2 = " + str(parameters["b2"]))
    print()

    print("测试forward_propagation")
    A2, cache = forward_propagation(X, parameters)
    print(np.mean(cache["Z1"]), np.mean(cache["A1"]), np.mean(cache["Z2"]), np.mean(cache["A2"]))
    print()

    print("测试compute_cost")
    print("cost = " + str(compute_cost(A2, Y)))
    print()

    print("测试backward_propagation")
    grads = backward_propagation(parameters, cache, X, Y)
    print("dW1 = " + str(grads["dW1"]))
    print("db1 = " + str(grads["db1"]))
    print("dW2 = " + str(grads["dW2"]))
    print("db2 = " + str(grads["db2"]))
    print()

    print("测试update_parameters")
    parameters = update_parameters(parameters, grads)
    print("W1 = " + str(parameters["W1"]))
    print("b1 = " + str(parameters["b1"]))
    print("W2 = " + str(parameters["W2"]))
    print("b2 = " + str(parameters["b2"]))
    print()

    print("测试nn_model")
    parameters = model(X, Y, 4, num_iterations=10000, print_cost=True)
    print("W1 = " + str(parameters["W1"]))
    print("b1 = " + str(parameters["b1"]))
    print("W2 = " + str(parameters["W2"]))
    print("b2 = " + str(parameters["b2"]))
    print()

    print("测试predict")
    predictions = predict(parameters, X)
    print("预测的平均值 = " + str(np.mean(predictions)))
    print()
