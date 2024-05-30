import matplotlib.pyplot as plt
import logistic_regression
import lr_utils

# train_set_x_orig, train_set_y, test_set_x_orig, test_set_y, classes = lr_utils.load_dataset()
# train_set_x_flatten = train_set_x_orig.reshape(train_set_x_orig.shape[0], -1).T
# test_set_x_flatten = test_set_x_orig.reshape(test_set_x_orig.shape[0], -1).T
# train_set_x = train_set_x_flatten / 255
# test_set_x = test_set_x_flatten / 255
# d = logistic_regression.model(train_set_x, train_set_y, test_set_x, test_set_y, num_iterations=2000,
#                               alpha=0.005,
#                               print_cost=True)
#
# # 绘制图
# plt.plot(d['Js'])
# plt.ylabel('J(w,b)')
# plt.xlabel('iterations (per hundreds)')
# plt.title("Learning rate (alpha) =" + str(d["alpha"]))
# plt.show()


train_set_x_orig, train_set_y, test_set_x_orig, test_set_y, classes = lr_utils.load_dataset()
train_set_x_flatten = train_set_x_orig.reshape(train_set_x_orig.shape[0], -1).T
test_set_x_flatten = test_set_x_orig.reshape(test_set_x_orig.shape[0], -1).T
train_set_x = train_set_x_flatten / 255
test_set_x = test_set_x_flatten / 255

learning_rates = [0.005, 0.01, 0.001, 0.0001]
models = {}
for i in learning_rates:
    print("learning rate is: " + str(i))
    print("num_iterations = 2000")
    models[str(i)] = logistic_regression.model(train_set_x, train_set_y, test_set_x, test_set_y, num_iterations=2000,
                                               alpha=i, print_cost=True)
    print('\n' + "-------------------------------------------------------" + '\n')

for i in learning_rates:
    plt.plot(models[str(i)]["Js"], label=str(models[str(i)]["alpha"]))

plt.ylabel('J(w,b)')
plt.xlabel('iterations (per hundreds)')

legend = plt.legend(loc='upper center', shadow=True)
frame = legend.get_frame()
frame.set_facecolor('0.90')
plt.show()
