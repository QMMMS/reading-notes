import turtle


def tur_circle():
    """用turtle画一个圆"""
    b = turtle.Turtle()
    for i in range(720):
        b.fd(1000 / 720)
        b.lt(360 / 720)


def tur_n_sided(n):
    """用turtle画一个正n边形"""
    b = turtle.Turtle()
    for i in range(n):
        b.fd(1000 / n)
        b.lt(360 / n)


def tur_n_sided_out():
    """用户自定义程序"""
    print("这个程序可以画一个正多边形")
    n0 = int(input("请输入正多边形的边数:"))
    tur_n_sided(n0)


def tur_n_sided_auto():
    """画一个好看的图形"""
    m = 6
    while m < 16:
        tur_n_sided(m)
        m += 1


def tur_arc(r, angle):
    """
    画弧
    :param r:半径
    :param angle:圆心角
    """
    arc_length = 2 * 3.1415 * r * angle / 360
    step_length = 3
    n = int(arc_length / step_length)
    step_angle = angle / n
    b = turtle.Turtle()
    for i in range(n):
        b.fd(step_length)
        b.lt(step_angle)


def tur_b_arc(r, angle):
    """书上的解 画弧"""
    arc_length = 2 * 3.1415 * r * angle / 360
    n = int(arc_length / 3) + 1
    step_length = arc_length / n
    step_angle = angle / n
    b = turtle.Turtle()
    for i in range(n):
        b.fd(step_length)
        b.lt(step_angle)


def tur_flower_1():
    """画花"""
    r = 120
    angle = 180
    arc_length = 2 * 3.1415 * r * angle / 360
    step_length = 3
    n = int(arc_length / step_length)
    step_angle = angle / n
    b = turtle.Turtle()
    m = int(720 / angle)
    for i_1 in range(m):
        for i_2 in range(n):
            b.fd(step_length)
            b.lt(step_angle)
        b.lt(angle / 2)


def tur_flower_2():
    """画花高级"""
    b = turtle.Turtle()
    r = 200
    angle = 45
    arc_length = 2 * 3.1415 * r * angle / 360
    step_length = 3
    n = int(arc_length / step_length)
    step_angle = angle / n
    for i_1 in range(int(360 / angle)):
        for i in range(n):
            b.fd(step_length)
            b.lt(step_angle)
        b.lt(angle * 2)
        for i in range(n):
            b.fd(step_length)
            b.lt(step_angle)
        b.lt(angle)


def tur_flower_0_1():
    len0 = 3
    b0.fd(len0)
    b0.lt(60)
    b0.fd(len0)
    b0.rt(120)
    b0.fd(len0)
    b0.lt(60)
    b0.fd(len0)


def tur_flower_0_2():
    tur_flower_0_1()
    b0.lt(60)
    tur_flower_0_1()
    b0.rt(120)
    tur_flower_0_1()
    b0.lt(60)
    tur_flower_0_1()


def tur_flower_0_3():
    tur_flower_0_2()
    b0.lt(60)
    tur_flower_0_2()
    b0.rt(120)
    tur_flower_0_2()
    b0.lt(60)
    tur_flower_0_2()


def tur_flower_0_4():
    tur_flower_0_3()
    b0.lt(60)
    tur_flower_0_3()
    b0.rt(120)
    tur_flower_0_3()
    b0.lt(60)
    tur_flower_0_3()


def tur_flower_3():
    tur_flower_0_4()
    b0.lt(60)
    tur_flower_0_4()
    b0.rt(120)
    tur_flower_0_4()
    b0.lt(60)
    tur_flower_0_4()


def tur(n):
    len0 = 5
    if n == 1:
        b0.fd(len0)
        b0.lt(60)
        b0.fd(len0)
        b0.rt(120)
        b0.fd(len0)
        b0.lt(60)
        b0.fd(len0)
    else:
        tur(n - 1)
        b0.lt(60)
        tur(n - 1)
        b0.rt(120)
        tur(n - 1)
        b0.lt(60)
        tur(n - 1)


if __name__ == '__main__':
    b0 = turtle.Turtle()
    b0.penup()
    b0.rt(180)
    b0.fd(200)
    b0.rt(180)
    b0.pendown()
    tur(5)
