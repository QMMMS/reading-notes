import matplotlib.pyplot as plt

from neural_network import *
import testCase

# 测试update_parameters_with_gd
print("-------------测试update_parameters_with_gd-------------")
parameters, grads, learning_rate = testCase.update_parameters_with_gd_test_case()
parameters = update_parameters_with_gd(parameters, grads, learning_rate)
print("W1 = " + str(parameters["W1"]))
print("b1 = " + str(parameters["b1"]))
print("W2 = " + str(parameters["W2"]))
print("b2 = " + str(parameters["b2"]))

# 测试random_mini_batches
print("-------------测试random_mini_batches-------------")
X_assess, Y_assess, mini_batch_size = testCase.random_mini_batches_test_case()
mini_batches = random_mini_batches(X_assess, Y_assess, mini_batch_size)
print("第1个mini_batch_X 的维度为：", mini_batches[0][0].shape)
print("第1个mini_batch_Y 的维度为：", mini_batches[0][1].shape)
print("第2个mini_batch_X 的维度为：", mini_batches[1][0].shape)
print("第2个mini_batch_Y 的维度为：", mini_batches[1][1].shape)
print("第3个mini_batch_X 的维度为：", mini_batches[2][0].shape)
print("第3个mini_batch_Y 的维度为：", mini_batches[2][1].shape)

# 测试initialize_velocity
print("-------------测试initialize_velocity-------------")
parameters = testCase.initialize_velocity_test_case()
v = initialize_velocity(parameters)
print('v["dW1"] = ' + str(v["dW1"]))
print('v["db1"] = ' + str(v["db1"]))
print('v["dW2"] = ' + str(v["dW2"]))
print('v["db2"] = ' + str(v["db2"]))

# 测试update_parameters_with_momentun
print("-------------测试update_parameters_with_momentun-------------")
parameters, grads, v = testCase.update_parameters_with_momentum_test_case()
update_parameters_with_momentun(parameters, grads, v, beta=0.9, learning_rate=0.01)
print("W1 = " + str(parameters["W1"]))
print("b1 = " + str(parameters["b1"]))
print("W2 = " + str(parameters["W2"]))
print("b2 = " + str(parameters["b2"]))
print('v["dW1"] = ' + str(v["dW1"]))
print('v["db1"] = ' + str(v["db1"]))
print('v["dW2"] = ' + str(v["dW2"]))
print('v["db2"] = ' + str(v["db2"]))

# 测试initialize_adam
print("-------------测试initialize_adam-------------")
parameters = testCase.initialize_adam_test_case()
v, s = initialize_adam(parameters)
print('v["dW1"] = ' + str(v["dW1"]))
print('v["db1"] = ' + str(v["db1"]))
print('v["dW2"] = ' + str(v["dW2"]))
print('v["db2"] = ' + str(v["db2"]))
print('s["dW1"] = ' + str(s["dW1"]))
print('s["db1"] = ' + str(s["db1"]))
print('s["dW2"] = ' + str(s["dW2"]))
print('s["db2"] = ' + str(s["db2"]))

# 测试update_with_parameters_with_adam
print("-------------测试update_with_parameters_with_adam-------------")
parameters, grads, v, s = testCase.update_parameters_with_adam_test_case()
update_parameters_with_adam(parameters, grads, v, s, t=2)
print("W1 = " + str(parameters["W1"]))
print("b1 = " + str(parameters["b1"]))
print("W2 = " + str(parameters["W2"]))
print("b2 = " + str(parameters["b2"]))
print('v["dW1"] = ' + str(v["dW1"]))
print('v["db1"] = ' + str(v["db1"]))
print('v["dW2"] = ' + str(v["dW2"]))
print('v["db2"] = ' + str(v["db2"]))
print('s["dW1"] = ' + str(s["dW1"]))
print('s["db1"] = ' + str(s["db1"]))
print('s["dW2"] = ' + str(s["dW2"]))
print('s["db2"] = ' + str(s["db2"]))
