"""
动态规划
子任务必须是离散的

任务：小偷模拟器（不是）
在有限的背包空间塞下总价值最高的物品
"""


def create_cost(bag_room):
    cost = {}
    for i in range(bag_room):
        cost[i + 1] = 0
    return cost


def find_max_value_and_items():
    global dictionary_of_items
    global room_of_bag
    last_cost = create_cost(room_of_bag)
    later_cost = {}
    temporary_items = {}
    final_items = {}
    for item, item_info in dictionary_of_items.items():
        item_value = item_info[0]
        item_weight = item_info[1]
        for weight, value in last_cost.items():
            if weight == item_weight:
                new_value = item_value
                if new_value > value:
                    later_cost[weight] = new_value
                    final_items[weight] = item
                else:
                    later_cost[weight] = value
            elif weight > item_weight:
                spare_weight = weight - item_weight
                new_value = item_value + last_cost[spare_weight]
                if new_value > value:
                    later_cost[weight] = new_value
                    if spare_weight in temporary_items:
                        final_items[weight] = temporary_items[spare_weight] + "," + item
                    else:
                        final_items[weight] = item
                else:
                    later_cost[weight] = value
            else:
                later_cost[weight] = value
        last_cost = later_cost
        later_cost = {}
        temporary_items.update(final_items)
        final_items = {}
    return last_cost[room_of_bag], temporary_items[room_of_bag]


if __name__ == '__main__':
    dictionary_of_items = {
        "音箱": [3000, 4],
        "笔记本": [2000, 3],
        "吉他": [1500, 1],
        "显示器": [2000, 1]
    }
    room_of_bag = 7
    target = find_max_value_and_items()
    print("物品总览：")
    for name, info in dictionary_of_items.items():
        print("%s:价格为%i元,重量为%i千克" % (name, info[0], info[1]))
    print()
    print("背包的最大承重为%i千克" % room_of_bag)
    print()
    print("电脑建议您拿" + target[1])
    print("这些物品的总价值为%i元" % target[0])
