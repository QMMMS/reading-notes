k = 2
while True:
    n = 2 * k
    num_list = []
    i = 2
    for i in range(2, n):
        m = 2
        for m in range(2, i):
            if i % m == 0:
                break
        else:
            num_list.append(i)
    for n_1 in num_list:
        for n_2 in num_list:
            if n_2 + n_1 == n:
                print("%d=%d+%d" % (n, n_1, n_2))
    k += 1
