import tensorflow._api.v2.compat.v1 as tf  # 导入包

tf.disable_eager_execution()

w = tf.Variable(0, dtype=tf.float32)  # tf.Variable()来定义变量参数
# cost = tf.add(tf.add(w ** 2, tf.multiply(- 10., w)), 25)  # 定义损失函数J
cost = w**2-10*w+25
train = tf.train.GradientDescentOptimizer(0.01).minimize(cost)  # 用0.01的学习率，目标是最小化损失
init = tf.global_variables_initializer()

session = tf.Session()  # 开启一个TensorFlow session
session.run(init)  # 来初始化全局变量
session.run(w)  # 将w初始化为0，并定义损失函数

for i in range(1000):
    session.run(train)  # 运行一步梯度下降法

print(session.run(w))
