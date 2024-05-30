import matplotlib.pyplot as plt
from dnn_utils import *


def initialize_parameters_deep(layers_dims):
    """
    初始化多层网络参数

    参数：
        layers_dims - 包含网络中每个图层(包括样本与最终结果)的节点数量的列表

    返回：
        parameters - 包含所有参数 W[l], b[l] 的字典
    """
    parameters = {}
    L = len(layers_dims)

    for l in range(1, L):
        parameters["W" + str(l)] = np.random.randn(layers_dims[l], layers_dims[l - 1]) / np.sqrt(layers_dims[l - 1])
        parameters["b" + str(l)] = np.zeros((layers_dims[l], 1))

        assert (parameters["W" + str(l)].shape == (layers_dims[l], layers_dims[l - 1]))
        assert (parameters["b" + str(l)].shape == (layers_dims[l], 1))

    return parameters


def linear_forward(A, W, b):
    """
    实现前向传播的线性部分

    参数：
        A - 来自上一层的激活值，维度为（n[l-1]，m）
        W - 权重矩阵，维度为（n[l]，n[l-1]）
        b - 偏置向量，维度为（n[l]，1）

    返回：
         Z - 激活功能的输入，也称为预激活参数，维度为（n[l-1]，m）
         cache - 一个包含“A”，“W”和“b”的元组，便于计算后向传递
    """

    Z = np.dot(W, A) + b
    assert (Z.shape == (W.shape[0], A.shape[1]))
    cache = (A, W, b)

    return Z, cache


def linear_activation_forward(A_prev, W, b, activation="relu"):
    """
    实现前向传播的线性部分和激活

    参数：
        A_prev - 来自上一层的激活值，维度为（n[l-1]，m）
        W - 权重矩阵，维度为（n[l]，n[l-1]）
        b - 偏置向量，维度为（n[l]，1）
        activation - 选择在此层中使用的激活函数名，字符串类型，【"sigmoid" | "relu"】

    返回：
        A - 激活函数的输出，也称为激活后的值
        cache - 一个包含“linear_cache”和“activation_cache”的元组，便于计算后向传递
            linear_cache - 包含 A, W, b
            activation_cache - 包含 Z
    """

    if activation == "sigmoid":
        Z, linear_cache = linear_forward(A_prev, W, b)
        A, activation_cache = sigmoid(Z)
    else:  # activation == "relu"
        Z, linear_cache = linear_forward(A_prev, W, b)
        A, activation_cache = relu(Z)

    assert (A.shape == (W.shape[0], A_prev.shape[1]))
    cache = (linear_cache, activation_cache)

    return A, cache


def L_model_forward(X, parameters):
    """
    实现多层网络的前向传播，为每一层都执行线性部分和激活

    参数：
        X - 输入数据，维度为（n[0]，m）
        parameters - 包含所有参数 W[l], b[l] 的字典

    返回：
        AL - 最后的激活值输出
        caches - 所有层的 cache，索引为从 0 到 L-1 ，最后一个对应 sigmoid ，前面都对应 relu
            cache - 包含linear_cache，activation_cache的元组
                linear_cache - 包含 A, W, b
                activation_cache - 包含 Z
    """
    caches = []
    A = X
    L = len(parameters) // 2  # 层数，//表示整除
    for l in range(1, L):
        A_prev = A
        A, cache = linear_activation_forward(A_prev, parameters['W' + str(l)], parameters['b' + str(l)], "relu")
        caches.append(cache)

    AL, cache = linear_activation_forward(A, parameters['W' + str(L)], parameters['b' + str(L)], "sigmoid")
    caches.append(cache)

    assert (AL.shape == (1, X.shape[1]))

    return AL, caches


def compute_cost(AL, Y):
    """
    计算成本

    参数：
        AL - 与标签预测相对应的概率向量，维度为（1，m）
        Y - 标签向量（例如：如果不是猫，则为0，如果是猫则为1），维度为（1，m）

    返回：
        cost - 交叉熵成本
    """
    m = Y.shape[1]
    cost = -np.sum(np.multiply(np.log(AL), Y) + np.multiply(np.log(1 - AL), 1 - Y)) / m
    cost = np.squeeze(cost)

    assert (cost.shape == ())

    return cost


def linear_backward(dZ, cache):
    """
    为单层实现反向传播的线性部分

    参数：
         dZ - 相对于（当前第l层的）线性输出的成本梯度
         cache - 来自当前层前向传播的值的元组（A_prev，W，b）

    返回：
         dA_prev - 相对于激活（前一层l-1）的成本梯度，与A_prev维度相同
         dW - 相对于W（当前层l）的成本梯度，与W的维度相同
         db - 相对于b（当前层l）的成本梯度，与b维度相同
    """
    A_prev, W, b = cache
    m = A_prev.shape[1]
    dW = np.dot(dZ, A_prev.T) / m
    db = np.sum(dZ, axis=1, keepdims=True) / m
    dA_prev = np.dot(W.T, dZ)

    assert (dA_prev.shape == A_prev.shape)
    assert (dW.shape == W.shape)
    assert (db.shape == b.shape)

    return dA_prev, dW, db


def linear_activation_backward(dA, cache, activation="relu"):
    """
    实现线性部分和激活的后向传播。

    参数：
         dA - 当前层l的激活后的梯度值
         cache - 包含linear_cache，activation_cache的元组
            linear_cache - 包含 A, W, b
            activation_cache - 包含 Z
         activation - 要在此层中使用的激活函数名，字符串类型，【"sigmoid" | "relu"】
    返回：
         dA_prev - 相对于激活（前一层l-1）的成本梯度值，与A_prev维度相同
         dW - 相对于W（当前层l）的成本梯度值，与W的维度相同
         db - 相对于b（当前层l）的成本梯度值，与b的维度相同
    """
    linear_cache, activation_cache = cache
    if activation == "relu":
        dZ = relu_backward(dA, activation_cache)
        dA_prev, dW, db = linear_backward(dZ, linear_cache)
    else:  # activation == "sigmoid"
        dZ = sigmoid_backward(dA, activation_cache)
        dA_prev, dW, db = linear_backward(dZ, linear_cache)

    return dA_prev, dW, db


def L_model_backward(AL, Y, caches):
    """
    多层网络的向后传播

    参数：
     AL - 概率向量，正向传播的输出，维度为（1，m）
     Y - 标签向量（例如：如果不是猫，则为0，如果是猫则为1），维度为（1，m）
     caches - 所有层的 cache，索引为从 0 到 L-1 ，最后一个对应 sigmoid ，前面都对应 relu
        cache - 包含linear_cache，activation_cache的元组
            linear_cache - 包含 A, W, b
            activation_cache - 包含 Z

    返回：
     grads - 包含所有层梯度值 dA, dW, db的字典，索引为从 0 到 L-1
    """
    grads = {}
    L = len(caches)
    Y = Y.reshape(AL.shape)
    dAL = - (np.divide(Y, AL) - np.divide(1 - Y, 1 - AL))

    current_cache = caches[L - 1]
    grads["dA" + str(L)], grads["dW" + str(L)], grads["db" + str(L)] \
        = linear_activation_backward(dAL, current_cache, "sigmoid")

    for l in reversed(range(L - 1)):
        current_cache = caches[l]
        dA_prev_temp, dW_temp, db_temp = linear_activation_backward(grads["dA" + str(l + 2)], current_cache, "relu")
        grads["dA" + str(l + 1)] = dA_prev_temp
        grads["dW" + str(l + 1)] = dW_temp
        grads["db" + str(l + 1)] = db_temp

    return grads


def update_parameters(parameters, grads, learning_rate):
    """
    使用梯度下降更新参数

    参数：
     parameters - 包含所有参数 W[l], b[l] 的字典
     grads - 包含所有层梯度值 dA, dW, db的字典，索引为从 0 到 L-1

    返回：
     parameters - 包含所有更新参数 W[l], b[l] 的字典
    """
    L = len(parameters) // 2
    for l in range(L):
        parameters["W" + str(l + 1)] = parameters["W" + str(l + 1)] - learning_rate * grads["dW" + str(l + 1)]
        parameters["b" + str(l + 1)] = parameters["b" + str(l + 1)] - learning_rate * grads["db" + str(l + 1)]

    return parameters


def two_layer_model(X, Y, layers_dims, learning_rate=0.0075, num_iterations=3000, print_cost=False):
    """
    实现一个两层的神经网络

    参数：
        X - 输入的数据，维度为(n_x，m)
        Y - 标签，向量，0为非猫，1为猫，维度为(1,m)
        layers_dims - 层数的向量，维度为(n_y,n_h,n_y)
        learning_rate - 学习率
        num_iterations - 迭代的次数
        print_cost - 是否打印成本值
    返回:
        parameters - 一个包含W1，b1，W2，b2的字典变量
        costs - 包含每一次迭代后的成本
    """
    grads = {}
    costs = []
    (n_x, n_h, n_y) = layers_dims

    # 初始化参数
    parameters = initialize_parameters_deep((n_x, n_h, n_y))
    W1 = parameters["W1"]
    b1 = parameters["b1"]
    W2 = parameters["W2"]
    b2 = parameters["b2"]

    # 进行迭代
    for i in range(0, num_iterations):
        # 前向传播
        A1, cache1 = linear_activation_forward(X, W1, b1, "relu")
        A2, cache2 = linear_activation_forward(A1, W2, b2, "sigmoid")

        # 计算成本
        cost = compute_cost(A2, Y)

        # 后向传播
        dA2 = - (np.divide(Y, A2) - np.divide(1 - Y, 1 - A2))
        dA1, dW2, db2 = linear_activation_backward(dA2, cache2, "sigmoid")
        dA0, dW1, db1 = linear_activation_backward(dA1, cache1, "relu")
        grads["dW1"] = dW1
        grads["db1"] = db1
        grads["dW2"] = dW2
        grads["db2"] = db2

        # 更新参数
        parameters = update_parameters(parameters, grads, learning_rate)
        W1 = parameters["W1"]
        b1 = parameters["b1"]
        W2 = parameters["W2"]
        b2 = parameters["b2"]

        # 打印成本值
        costs.append(cost)
        if print_cost:
            print("第", i, "次迭代，成本值为：", np.squeeze(cost))

    return parameters, costs


def L_layer_model(X, Y, layers_dims, learning_rate=0.0075, num_iterations=3000, print_cost=False):
    """
    实现一个L层神经网络

    参数：
        X - 输入的数据，维度为(n_x，m)
        Y - 标签，向量，0为非猫，1为猫，维度为(1,m)
        layers_dims - 包含网络中每个图层(包括样本与最终结果)的节点数量的列表
        learning_rate - 学习率
        num_iterations - 迭代的次数
        print_cost - 是否打印成本值

    返回：
         parameters - 所有模型学习的参数 W, b
         costs - 包含每一次迭代后的成本
    """
    costs = []

    # 初始化参数
    parameters = initialize_parameters_deep(layers_dims)

    for i in range(0, num_iterations):
        AL, caches = L_model_forward(X, parameters)  # 前向传播
        cost = compute_cost(AL, Y)  # 计算成本
        grads = L_model_backward(AL, Y, caches)  # 后向传播
        parameters = update_parameters(parameters, grads, learning_rate)  # 更新参数

        # 打印成本值
        costs.append(cost)
        if print_cost:
            print("第", i, "次迭代，成本值为：", np.squeeze(cost))

    return parameters, costs


def predict(X, y, parameters):
    """
    该函数用于预测L层神经网络的结果

    参数：
         X - 测试集
         y - 标签
         parameters - 训练模型的参数 W, b

    返回：
        p - 给定数据集X的预测
    """

    m = X.shape[1]
    p = np.zeros((1, m))

    # 根据参数前向传播
    AL, caches = L_model_forward(X, parameters)

    for i in range(0, AL.shape[1]):
        if AL[0, i] > 0.5:
            p[0, i] = 1
        else:
            p[0, i] = 0

    print("准确度为: " + str(float(np.sum((p == y)) / m)))

    return p


def print_mislabeled_images(classes, X, y, p):
    """
    绘制预测和实际不同的图像

    参数：
        X - 数据集
        y - 实际的标签
        p - 预测
    """
    a = p + y
    mislabeled_indices = np.asarray(np.where(a == 1))
    num_images = len(mislabeled_indices[0])
    row_nums = int(np.sqrt(num_images)) + 1
    for i in range(num_images):
        index = mislabeled_indices[1][i]

        plt.subplot(row_nums, row_nums, i + 1)
        plt.imshow(X[:, index].reshape(64, 64, 3), interpolation='nearest')
        plt.axis('off')
        plt.title(
            "Prediction: " + classes[int(p[0, index])].decode("utf-8") + " \n Class: " + classes[y[0, index]].decode(
                "utf-8"))
    plt.show()
