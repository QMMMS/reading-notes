import numpy as np
import h5py
import matplotlib.pyplot as plt


def load_dataset():
    # H5文件是以层级数据格式（HDF）第5版保存的数据文件，它包含科学数据的多维数组。
    train_dataset = h5py.File('datasets/train_catvnoncat.h5', "r")

    train_set_x_orig = np.array(train_dataset["train_set_x"][:])  # your train set features
    train_set_y_orig = np.array(train_dataset["train_set_y"][:])  # your train set labels

    test_dataset = h5py.File('datasets/test_catvnoncat.h5', "r")
    test_set_x_orig = np.array(test_dataset["test_set_x"][:])  # your test set features
    test_set_y_orig = np.array(test_dataset["test_set_y"][:])  # your test set labels

    classes = np.array(test_dataset["list_classes"][:])  # the list of classes

    train_set_y_orig = train_set_y_orig.reshape((1, train_set_y_orig.shape[0]))
    test_set_y_orig = test_set_y_orig.reshape((1, test_set_y_orig.shape[0]))

    return train_set_x_orig, train_set_y_orig, test_set_x_orig, test_set_y_orig, classes


if __name__ == '__main__':
    train_set_x_orig, train_set_y_orig, test_set_x_orig, test_set_y_orig, classes = load_dataset()

    print("展示维度")
    print("train_set_x_orig.shape = ", train_set_x_orig.shape)
    print("train_set_y_orig.shape = ", train_set_y_orig.shape)
    print("test_set_x_orig.shape = ", test_set_x_orig.shape)
    print("test_set_y_orig.shape = ", test_set_y_orig.shape)
    print()

    print("展示信息")
    m_train = train_set_y_orig.shape[1]  # 训练集里图片的数量。
    m_test = test_set_y_orig.shape[1]  # 测试集里图片的数量。
    num_px = train_set_x_orig.shape[1]  # 训练、测试集里面的图片的宽度和高度（均为64x64）。

    print("训练集的数量: m_train = " + str(m_train))
    print("测试集的数量 : m_test = " + str(m_test))
    print("每张图片的宽/高 : num_px = " + str(num_px))
    print("每张图片的大小 : " + str(train_set_x_orig[0].shape))
    print("训练集_图片的维数 : " + str(train_set_x_orig.shape))
    print("训练集_标签的维数 : " + str(train_set_y_orig.shape))
    print("测试集_图片的维数: " + str(test_set_x_orig.shape))
    print("测试集_标签的维数: " + str(test_set_y_orig.shape))
    print()

    print("矩阵降维")
    # 把数组变为209列的矩阵（209张图片），-1告诉程序自动算列，变成了209行，12288列的矩阵，再转置
    # 这里的reshape以行优先填充，每行就是一个完整的图片样本，转置后每列是一个完整的图片样本
    # 下面的代码与train_set_x_flatten = train_set_x_orig.reshape(-1, train_set_x_orig.shape[0])不一样
    train_set_x_flatten = train_set_x_orig.reshape(train_set_x_orig.shape[0], -1).T
    test_set_x_flatten = test_set_x_orig.reshape(test_set_x_orig.shape[0], -1).T
    print("训练集降维最后的维度： " + str(train_set_x_flatten.shape))
    print("训练集_标签的维数 : " + str(train_set_y_orig.shape))
    print("测试集降维之后的维度: " + str(test_set_x_flatten.shape))
    print("测试集_标签的维数 : " + str(test_set_y_orig.shape))
    print()

    print("均值化")
    # 像素值实际上是从0到255范围内的三个数字的向量。
    # 机器学习中一个常见的预处理步骤是对数据集进行居中和标准化
    # 除以255，让标准化的数据位于 [0,1] 之间
    train_set_x = train_set_x_flatten / 255
    test_set_x = test_set_x_flatten / 255
    print()

    print("展示图片")
    for index in range(1, 17):
        plt.subplot(4, 4, index)  # subplot展示4*4个图片，把当前图片放在index位
        plt.imshow(train_set_x_orig[index])
        print("y=", train_set_y_orig[:, index], ", it's a " + classes[
            np.squeeze(train_set_y_orig[:, index])].decode("utf-8") + " picture")
        # 使用np.squeeze的目的是压缩维度，train_set_y[:,index]的值为[1] , np.squeeze(train_set_y[:,index])的值为1
    plt.show()
    print()
