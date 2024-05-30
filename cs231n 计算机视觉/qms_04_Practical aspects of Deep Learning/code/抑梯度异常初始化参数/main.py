import matplotlib.pyplot as plt
import deep_neural_networks
import init_utils

train_X, train_Y, test_X, test_Y = init_utils.load_dataset()
parameters = deep_neural_networks.model(train_X, train_Y, initialization="he", is_plot=True)
print("训练集:", end=" ")
predictions_train = init_utils.predict(train_X, train_Y, parameters)
print("测试集:", end=" ")
predictions_test = init_utils.predict(test_X, test_Y, parameters)

plt.title("Model with large he initialization")
axes = plt.gca()
axes.set_xlim([-1.5, 1.5])
axes.set_ylim([-1.5, 1.5])
init_utils.plot_decision_boundary(lambda x: init_utils.predict_dec(parameters, x.T), train_X, train_Y)
