"""
广度优先搜索适用于非加权图

狄克斯特拉算法
不断找到最短长度的节点，计算相邻节点长度，比较并更新
适用于加权图
但不能有负权重

若有负权重
换用贝尔曼—福德算法
"""


def make_graph():
    """
     +----6---->a----1----->
     |          ^
    start       3         end
     |          |
     +----2---->b----5----->
    :return: graph
    """
    graph0 = {}
    graph0["start"] = {}
    graph0["start"]["a"] = 6
    graph0["start"]["b"] = 2
    graph0["a"] = {}
    graph0["a"]["end"] = 1
    graph0["b"] = {}
    graph0["b"]["a"] = 3
    graph0["b"]["end"] = 5
    graph0["end"] = {}
    return graph0


def make_dictionary_of_costs(target_graph):
    infinity = float("inf")
    final_costs = {}
    for item in target_graph:
        if item == "start":
            final_costs[item] = 0
        else:
            final_costs[item] = infinity
    return final_costs


def find_lowest_cost_node(node0s):
    compare = float("inf")
    final_node = None
    for node0 in node0s:
        if node0s[node0] < compare:
            final_node = node0
            compare = node0s[node0]
    return final_node


def find_path(dictionary_of_parents):
    child = "end"
    print(child, end="<--")
    parent = dictionary_of_parents[child]
    while parent != "start":
        print(parent, end="<--")
        child = parent
        parent = dictionary_of_parents[child]
    print("start")


def find_lowest_rank_and_parents(target_graph):
    parents = {}
    costs = make_dictionary_of_costs(target_graph)
    processed = []

    node = find_lowest_cost_node(costs)
    while len(costs) != 1:
        cost = costs[node]
        neighbors = target_graph[node]  # 字典
        # print(neighbors)
        for neighbor in neighbors:
            if neighbor not in processed:
                neighbor_cost = neighbors[neighbor]
                new_cost = cost + int(neighbor_cost)
                if new_cost < costs[neighbor]:
                    costs[neighbor] = new_cost
                    parents[neighbor] = node
        costs.pop(node)
        processed.append(node)
        node = find_lowest_cost_node(costs)
    return str(costs["end"]), parents


if __name__ == '__main__':
    graph = make_graph()
    print(graph)
    print("到终点的最短长度为：" + find_lowest_rank_and_parents(graph)[0])
    print("路劲为：", end="")
    find_path(find_lowest_rank_and_parents(graph)[1])
