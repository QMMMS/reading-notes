import matplotlib.pyplot as plt
import deep_neural_networks
import reg_utils

train_X, train_Y, test_X, test_Y = reg_utils.load_2D_dataset()

# Model without regularization

parameters = deep_neural_networks.model(train_X, train_Y, is_plot=True)
print("训练集:", end=" ")
reg_utils.predict(train_X, train_Y, parameters)
print("测试集:", end=" ")
reg_utils.predict(test_X, test_Y, parameters)

plt.title("Model without regularization")
axes = plt.gca()
axes.set_xlim([-0.75, 0.40])
axes.set_ylim([-0.75, 0.65])
reg_utils.plot_decision_boundary(lambda x: reg_utils.predict_dec(parameters, x.T), train_X, train_Y)

# Model with L2 regularization

parameters = deep_neural_networks.model(train_X, train_Y, lambd=0.7, is_plot=True)
print("训练集:", end=" ")
reg_utils.predict(train_X, train_Y, parameters)
print("测试集:", end=" ")
reg_utils.predict(test_X, test_Y, parameters)

plt.title("Model with L2 regularization")
axes = plt.gca()
axes.set_xlim([-0.75, 0.40])
axes.set_ylim([-0.75, 0.65])
reg_utils.plot_decision_boundary(lambda x: reg_utils.predict_dec(parameters, x.T), train_X, train_Y)

# Model with dropout regularization

parameters = deep_neural_networks.model(train_X, train_Y, keep_prob=0.86, is_plot=True)
print("训练集:", end=" ")
reg_utils.predict(train_X, train_Y, parameters)
print("测试集:", end=" ")
reg_utils.predict(test_X, test_Y, parameters)

plt.title("Model with dropout regularization")
axes = plt.gca()
axes.set_xlim([-0.75, 0.40])
axes.set_ylim([-0.75, 0.65])
reg_utils.plot_decision_boundary(lambda x: reg_utils.predict_dec(parameters, x.T), train_X, train_Y)
