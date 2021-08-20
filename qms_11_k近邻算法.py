"""
懒惰学习典范
"""
from random import randint


def create_fruit_info():
    # 大小，香味，颜色，软硬，价格
    target_fruit_info = {
        "apple1": [10, 9, 1, 10, 8],
        "apple2": [9, 7, 2, 9, 10],
        "apple3": [8, 9, 3, 8, 7],
        "orange1": [4, 3, 7, 1, 4],
        "orange2": [2, 4, 9, 2, 3],
        "orange3": [1, 2, 6, 4, 2]
    }
    return target_fruit_info


def create_new_fruit():
    new_fruit_info = []
    for i in range(5):
        random_num = randint(1, 10)
        new_fruit_info.append(random_num)
    return new_fruit_info


def compare_fruit(new_fruit_info, target_fruit_info):
    final_fruit_info = []
    compare = float("inf")
    for fruit, info in target_fruit_info.items():
        rank = 0
        for n in range(5):
            new_rank = (new_fruit_info[n] - info[n]) ** 2
            rank += new_rank
        if rank < compare:
            final_fruit_info.clear()
            final_fruit_info.append(fruit)
            compare = rank
        elif rank == compare:
            final_fruit_info.append(fruit)
    return final_fruit_info


def give_answer(final_fruit_info):
    num_of_apples = 0
    num_of_oranges = 0
    for fruit in final_fruit_info:
        if fruit.startswith("apple"):
            num_of_apples += 1
        else:
            num_of_oranges += 1
    if num_of_apples > num_of_oranges:
        print("电脑觉得这是一个苹果")
    elif num_of_oranges > num_of_apples:
        print("电脑觉得这是一个橙子")
    else:
        print("唔...不知道呢...")


if __name__ == '__main__':
    fruit_info = create_fruit_info()
    new_fruit = create_new_fruit()
    final_fruit = compare_fruit(new_fruit, fruit_info)
    print("这有一个果子，大小为%i，香味为%i，颜色为%i，软硬度为%i，价格为%i"
          % (new_fruit[0], new_fruit[1], new_fruit[2], new_fruit[3], new_fruit[4]))
    give_answer(final_fruit)
