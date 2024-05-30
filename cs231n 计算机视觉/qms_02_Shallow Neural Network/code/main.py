import numpy as np
import matplotlib.pyplot as plt
import neural_networks
import planar_utils

X, Y = planar_utils.load_planar_dataset()
index = 1

for i in [5, 10, 20, 40]:
    parameters = neural_networks.model(X, Y, n_h=i, num_iterations=10000, learning_rate=0.5, print_cost=True)

    plt.subplot(2, 2, index)
    index += 1
    planar_utils.plot_decision_boundary(lambda x: neural_networks.predict(parameters, x.T), X, Y)  # 绘制边界
    plt.title("Decision Boundary for hidden layer size " + str(i))

    predictions = neural_networks.predict(parameters, X)
    print('准确率: %d' % float((np.dot(Y, predictions.T) + np.dot(1 - Y, 1 - predictions.T)) / float(Y.size) * 100) + '%')
plt.show()
