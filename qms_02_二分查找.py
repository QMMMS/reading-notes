"""
二分查找
必须是有序列表
O(log n)
"""


def find_index():
    low = 0
    high = len(num_list) - 1
    while 1:
        middle_index = int((low + high) / 2)
        middle_num = num_list[middle_index]
        if low > high:
            return "不存在！"
        elif target == middle_num:
            return str(middle_index)
        elif target > middle_num:
            low = middle_index + 1
        else:
            high = middle_index - 1


if __name__ == '__main__':
    # 创建一个有序数组
    num_list = []
    for i in range(10, 4000000):
        if i % 2 == 1:
            num_list.append(i)
    print(num_list)

    target = int(input("你要找："))  # 目标
    print("索引为：" + find_index())
