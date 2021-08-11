"""
D&C算法   快速排序
O(nlog(n))

任务：为一个随机数字列表排序
"""
from random import randint


def make_number_list():
    list_of_number = []
    number_of_number = randint(30000, 50000)
    for i in range(number_of_number):
        random_number = randint(1, 9999999999)
        list_of_number.append(random_number)
    return list_of_number


def sort_number(num_list):
    if len(num_list) < 2:
        return num_list
    else:
        compare = num_list[0]
        smaller = []
        larger = []
        for num in num_list[1:]:
            if num <= compare:
                smaller.append(num)
            else:
                larger.append(num)
        return sort_number(smaller) + [compare] + sort_number(larger)


if __name__ == '__main__':
    number_list = make_number_list()
    print("排序前：" + str(number_list))
    for n in range(20):
        print()
    print("排序后：" + str(sort_number(number_list)))
