import testCases
from deep_neural_networks import *


if __name__ == '__main__':
    print("==============测试initialize_parameters_deep==============")
    layers_dims = [5, 4, 3]
    parameters = initialize_parameters_deep(layers_dims)
    print("W1 = " + str(parameters["W1"]))
    print("b1 = " + str(parameters["b1"]))
    print("W2 = " + str(parameters["W2"]))
    print("b2 = " + str(parameters["b2"]))
    print()

    print("==============测试linear_forward==============")
    A, W, b = testCases.linear_forward_test_case()
    Z, linear_cache = linear_forward(A, W, b)
    print("Z = " + str(Z))
    print()

    # 测试linear_activation_forward
    print("==============测试linear_activation_forward==============")
    A_prev, W, b = testCases.linear_activation_forward_test_case()
    A = linear_activation_forward(A_prev, W, b, activation="sigmoid")[0]
    print("sigmoid，A = " + str(A))

    A = linear_activation_forward(A_prev, W, b, activation="relu")[0]
    print("ReLU，A = " + str(A))
    print()

    # 测试L_model_forward
    print("==============测试L_model_forward==============")
    X, parameters = testCases.L_model_forward_test_case()
    AL, caches = L_model_forward(X, parameters)
    print("AL = " + str(AL))
    print("caches 的长度为 = " + str(len(caches)))
    print()

    # 测试compute_cost
    print("==============测试compute_cost==============")
    Y, AL = testCases.compute_cost_test_case()
    print("cost = " + str(compute_cost(AL, Y)))
    print()

    # 测试linear_backward
    print("==============测试linear_backward==============")
    dZ = testCases.linear_backward_test_case()[0]

    dA_prev, dW, db = linear_backward(dZ, linear_cache)
    print("dA_prev = " + str(dA_prev))
    print("dW = " + str(dW))
    print("db = " + str(db))
    print()

    # 测试linear_activation_backward
    print("==============测试linear_activation_backward==============")
    AL, linear_activation_cache = testCases.linear_activation_backward_test_case()

    dA_prev, dW, db = linear_activation_backward(AL, linear_activation_cache, activation="sigmoid")
    print("sigmoid:")
    print("dA_prev = " + str(dA_prev))
    print("dW = " + str(dW))
    print("db = " + str(db) + "\n")

    dA_prev, dW, db = linear_activation_backward(AL, linear_activation_cache, activation="relu")
    print("relu:")
    print("dA_prev = " + str(dA_prev))
    print("dW = " + str(dW))
    print("db = " + str(db))
    print()

    # 测试L_model_backward
    print("==============测试L_model_backward==============")
    AL, Y_assess, caches = testCases.L_model_backward_test_case()
    grads = L_model_backward(AL, Y_assess, caches)
    print("dW1 = " + str(grads["dW1"]))
    print("db1 = " + str(grads["db1"]))
    print("dA1 = " + str(grads["dA1"]))
    print()

    # 测试update_parameters
    print("==============测试update_parameters==============")
    parameters, grads = testCases.update_parameters_test_case()
    parameters = update_parameters(parameters, grads, 0.1)

    print("W1 = " + str(parameters["W1"]))
    print("b1 = " + str(parameters["b1"]))
    print("W2 = " + str(parameters["W2"]))
    print("b2 = " + str(parameters["b2"]))
    print()
