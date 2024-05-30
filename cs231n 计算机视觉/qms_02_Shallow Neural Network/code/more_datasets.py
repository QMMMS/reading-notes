import numpy as np
import matplotlib.pyplot as plt
import neural_networks
import planar_utils

# 数据集
planar = planar_utils.load_planar_dataset()
noisy_circles, noisy_moons, blobs, gaussian_quantiles, no_structure = planar_utils.load_extra_datasets()
datasets = [planar, noisy_circles, noisy_moons, blobs, gaussian_quantiles, no_structure]
index = 1

for dataset in datasets:
    X, Y = dataset

    if index != 1:
        X, Y = X.T, Y.reshape(1, Y.shape[0])
        if dataset == "blobs":
            Y = Y % 2

    parameters = neural_networks.model(X, Y, n_h=5, num_iterations=10000, learning_rate=0.5, print_cost=True)

    plt.subplot(3, 2, index)
    index += 1
    planar_utils.plot_decision_boundary(lambda x: neural_networks.predict(parameters, x.T), X, Y)  # 绘制边界
    plt.title("Decision Boundary for hidden layer size " + str(5))

    predictions = neural_networks.predict(parameters, X)
    print('准确率: %d' % float((np.dot(Y, predictions.T) + np.dot(1 - Y, 1 - predictions.T)) / float(Y.size) * 100) + '%')
plt.show()
