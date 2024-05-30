import numpy as np
import tensorflow._api.v2.compat.v1 as tf

tf.disable_eager_execution()

w = tf.Variable(0, dtype=tf.float32)
x = tf.placeholder(tf.float32, [3, 1])  # 训练数据x, [3,1]数组, placeholder函数表示稍后会为x提供数值
cost = x[0][0] * w ** 2 + x[1][0] * w + x[2][0]
train = tf.train.GradientDescentOptimizer(0.01).minimize(cost)
init = tf.global_variables_initializer()

session = tf.Session()
session.run(init)
session.run(w)

coefficients = np.array([[1.], [-10.], [25.]])  # 准备接入x的数据
for i in range(1000):
    session.run(train, feed_dict={x: coefficients})

print(session.run(w))
