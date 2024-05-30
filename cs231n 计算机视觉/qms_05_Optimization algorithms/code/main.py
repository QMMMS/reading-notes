from neural_network import *

train_X, train_Y = opt_utils.load_dataset(is_plot=True)
plt.show()

# 使用普通的梯度下降
# layers_dims = [train_X.shape[0], 5, 2, 1]
# parameters = model(train_X, train_Y, layers_dims, optimizer="gd", is_plot=True)

# 使用动量的梯度下降
# layers_dims = [train_X.shape[0], 5, 2, 1]
# parameters = model(train_X, train_Y, layers_dims, beta=0.9, optimizer="momentum", is_plot=True)

# 使用Adam优化的梯度下降
layers_dims = [train_X.shape[0], 5, 2, 1]
parameters = model(train_X, train_Y, layers_dims, optimizer="adam", is_plot=True)

# 预测
predictions = opt_utils.predict(train_X, train_Y, parameters)

plt.title("Model")
axes = plt.gca()
axes.set_xlim([-1.5, 2.5])
axes.set_ylim([-1, 1.5])
opt_utils.plot_decision_boundary(lambda x: opt_utils.predict_dec(parameters, x.T), train_X, train_Y)
