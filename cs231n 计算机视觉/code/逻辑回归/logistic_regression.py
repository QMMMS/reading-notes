import numpy as np
import lr_utils


def sigmoid(z):
    """
    计算 sigmoid（z）

    参数：
        z  - 任何大小的标量或numpy数组。

    返回：
        s  -  sigmoid（z）
    """
    s = 1 / (1 + np.exp(-z))
    return s


def initialize_with_zeros(dim):
    """
        初始化需要的参数w和b，为w创建一个维度为（dim，1）的0向量，并将b初始化为0。

        参数：
            dim  - 我们想要的w矢量的大小（或者这种情况下的参数数量）

        返回：
            w  - 维度为（dim，1）的初始化向量。
            b  - 初始化的标量（对应于偏差）
    """
    w = np.zeros(shape=(dim, 1))
    b = 0
    # 使用断言来确保我要的数据是正确的
    assert (w.shape == (dim, 1))  # w的维度是(dim,1)
    assert (isinstance(b, float) or isinstance(b, int))  # b的类型是float或者是int

    return w, b


def propagate(w, b, X, Y):
    """
    实现一轮前向和后向传播的成本函数及其梯度。

    参数：
        w  - 权重，大小不等的数组（num_px * num_px * 3，1）
        b  - 偏差，一个标量
        X  - 输入数据，矩阵类型为（num_px * num_px * 3，训练数量）
        Y  - 标签（如果非猫则为0，如果是猫则为1），矩阵维度为(1,训练数据数量)

    返回：
        dw  - 相对于w的损失梯度，形状与w相同
        db  - 相对于b的损失梯度，形状与b相同
        J   - 逻辑回归的负对数似然成本
    """
    m = X.shape[1]  # 训练数量

    # 正向传播
    Z = np.dot(w.T, X) + b
    A = sigmoid(Z)  # 计算激活值
    J = (- 1 / m) * np.sum(Y * np.log(A) + (1 - Y) * (np.log(1 - A)))  # 计算成本/代价

    # 反向传播
    dZ = A - Y
    dw = (1 / m) * np.dot(X, dZ.T)
    db = (1 / m) * np.sum(dZ)

    # 使用断言确保我的数据是正确的
    assert (dw.shape == w.shape)
    assert (db.dtype == float)
    J = np.squeeze(J)
    J = np.float64(J)
    assert (J.shape == ())

    return dw, db, J


def optimize(w, b, X, Y, num_iterations, alpha, print_cost=True):
    """
    此函数通过运行梯度下降算法来优化w和b

    参数：
        w  - 权重，大小不等的数组（num_px * num_px * 3，1）
        b  - 偏差，一个标量
        X  - 输入数据，矩阵类型为（num_px * num_px * 3，训练数量）
        Y  - 标签（如果非猫则为0，如果是猫则为1），矩阵维度为(1,训练数据数量)
        num_iterations  - 优化循环的迭代次数
        alpha  - 梯度下降更新规则的学习率
        print_cost  - 每100步打印一次损失值

    返回：
        w  - 优化后的权重w
        b  - 优化后的偏差b
        dw  - 相对于w的损失梯度，形状与w相同
        db  - 相对于b的损失梯度，形状与b相同
        Js - 优化期间计算的所有成本列表，将用于绘制学习曲线。
    """
    global dw, db
    Js = []
    for i in range(num_iterations):
        dw, db, J = propagate(w, b, X, Y)
        w = w - alpha * dw
        b = b - alpha * db

        # 记录成本
        if i % 100 == 0:
            Js.append(J)
        # 打印成本数据
        if print_cost and (i % 100 == 0):
            print("迭代的次数: %i ， 误差值： %f" % (i, J))

    return w, b, dw, db, Js


def predict(w, b, X):
    """
    使用学习逻辑回归参数logistic （w，b）预测标签是0还是1，

    参数：
        w  - 权重，大小不等的数组（num_px * num_px * 3，1）
        b  - 偏差，一个标量
        X  - 输入数据，矩阵类型为（num_px * num_px * 3，训练数量）

    返回：
        Y_prediction  - 包含X中所有图片的所有预测【0 | 1】,矩阵维度为(1,训练数据数量)
    """
    m = X.shape[1]  # 图片训练数据数量
    Y_prediction = np.zeros((1, m))
    w = w.reshape(X.shape[0], 1)

    # 预测猫在图片中出现的概率
    A = sigmoid(np.dot(w.T, X) + b)
    for i in range(A.shape[1]):
        Y_prediction[0, i] = 1 if A[0, i] > 0.5 else 0

    assert (Y_prediction.shape == (1, m))

    return Y_prediction


def model(X_train, Y_train, X_test, Y_test, num_iterations=2000, alpha=0.5, print_cost=True):
    """
    通过调用之前实现的函数来构建逻辑回归模型

    参数：
        X_train  - numpy的数组,维度为（num_px * num_px * 3，m_train）的训练集
        Y_train  - numpy的数组,维度为（1，m_train）（矢量）的训练标签集
        X_test   - numpy的数组,维度为（num_px * num_px * 3，m_test）的测试集
        Y_test   - numpy的数组,维度为（1，m_test）（向量）的测试标签集
        num_iterations  - 表示用于优化参数的迭代次数的超参数
        alpha  - 表示optimize（）更新规则中使用的学习速率的参数
        print_cost  - 设置为true以每100次迭代打印成本

    返回：
        d  - 包含有关模型信息的字典。
    """
    w, b = initialize_with_zeros(X_train.shape[0])

    w, b, dw, db, Js = optimize(w, b, X_train, Y_train, num_iterations, alpha, print_cost)

    # 预测测试/训练集的例子
    Y_prediction_test = predict(w, b, X_test)
    Y_prediction_train = predict(w, b, X_train)

    # 打印训练后的准确性 ,np.mean()计算矩阵的均值
    print("训练集准确性：", format(100 - np.mean(np.abs(Y_prediction_train - Y_train)) * 100), "%")
    print("测试集准确性：", format(100 - np.mean(np.abs(Y_prediction_test - Y_test)) * 100), "%")

    d = {
        "Js": Js,
        "Y_prediction_test": Y_prediction_test,
        "Y_prediction_train": Y_prediction_train,
        "w": w,
        "b": b,
        "alpha": alpha,
        "num_iterations": num_iterations
    }
    return d


if __name__ == '__main__':
    print("测试sigmoid")
    print("sigmoid(0) = " + str(sigmoid(0)))
    print("sigmoid(9.2) = " + str(sigmoid(9.2)))
    print()

    print("测试propagate")
    w, b, X, Y = np.array([[1], [2]]), 2, np.array([[1, 2], [3, 4]]), np.array([[1, 0]])
    dw, db, J = propagate(w, b, X, Y)
    print("dw = " + str(dw))
    print("db = " + str(db))
    print("J = " + str(J))
    print()

    print("测试optimize")
    w, b, X, Y = np.array([[1], [2]]), 2, np.array([[1, 2], [3, 4]]), np.array([[1, 0]])
    w, b, dw, db, Js = optimize(w, b, X, Y, num_iterations=100, alpha=0.009, print_cost=True)
    print("w = " + str(w))
    print("b = " + str(b))
    print("dw = " + str(dw))
    print("db = " + str(db))
    print()

    print("测试predict")
    w, b, X, Y = np.array([[1], [2]]), 2, np.array([[1, 2], [3, 4]]), np.array([[1, 0]])
    print("predictions = " + str(predict(w, b, X)))
    print()

    print("测试model")
    train_set_x_orig, train_set_y_orig, test_set_x_orig, test_set_y_orig, classes = lr_utils.load_dataset()
    train_set_x_flatten = train_set_x_orig.reshape(-1, train_set_x_orig.shape[0])
    test_set_x_flatten = test_set_x_orig.reshape(-1, test_set_x_orig.shape[0])
    train_set_x = train_set_x_flatten / 255
    test_set_x = test_set_x_flatten / 255
    d = model(train_set_x, train_set_y_orig, test_set_x, test_set_y_orig, num_iterations=2000, alpha=0.005,
              print_cost=True)
