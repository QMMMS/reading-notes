import numpy as np
import matplotlib.pyplot as plt
import lr_utils
import deep_neural_networks

# 处理样本数据
train_set_x_orig, train_set_y, test_set_x_orig, test_set_y, classes = lr_utils.load_dataset()
train_x_flatten = train_set_x_orig.reshape(train_set_x_orig.shape[0], -1).T
test_x_flatten = test_set_x_orig.reshape(test_set_x_orig.shape[0], -1).T
train_x = train_x_flatten / 255
train_y = train_set_y
test_x = test_x_flatten / 255
test_y = test_set_y

# 训练
layers_dims = [12288, 20, 7, 5, 1]
parameters, costs = deep_neural_networks.L_layer_model(train_x, train_y, layers_dims,
                                                       learning_rate=0.0055, num_iterations=1000, print_cost=True)

# 测试准确率
predictions_train = deep_neural_networks.predict(train_x, train_y, parameters)  # 训练集
predictions_test = deep_neural_networks.predict(test_x, test_y, parameters)  # 测试集

# 画图
plt.plot(np.squeeze(costs))
plt.ylabel('cost')
plt.xlabel('iterations')
plt.title("Learning rate =" + str(0.0055))
plt.show()
deep_neural_networks.print_mislabeled_images(classes, test_x, test_y, predictions_test)
