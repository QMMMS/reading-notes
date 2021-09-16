"""
O(顶点数+边数)

任务：在朋友圈中找到博士
"""
from collections import deque


def make_a_friends_graph():
    # 创建一个朋友表
    friends_graph = {}
    """
                     ----Dr.jerry---- 
                    anuj          thom
                     -              -
                     -              -
                    bob-----I----clarie------jonny
                    -       -
                    -       -
                   peggy--alice
    """
    friends_graph["I"] = ["alice", "bob", "clarie"]
    friends_graph["alice"] = ["I", "peggy"]
    friends_graph["clarie"] = ["I", "jonny", "thom"]
    friends_graph["bob"] = ["I", "anuj", "peggy"]
    friends_graph["anuj"] = ["bob", "Dr.jerry"]
    friends_graph["thom"] = ["clarie", "Dr.jerry"]
    friends_graph["peggy"] = ["bob", "alice"]
    friends_graph["jonny"] = ["clarie"]
    friends_graph["Dr.jerry"] = ["anuj", "thom"]
    return friends_graph


def is_there_a_doctor(graph):
    search_queue = deque()
    search_queue += graph["I"]
    searched = []
    while search_queue:
        person = search_queue.popleft()
        if person.startswith("Dr."):
            return "我的朋友里有一个博士！"
        else:
            if person not in searched:
                search_queue += graph[person]
                searched.append(person)
    return "我的朋友里没有博士！"


if __name__ == '__main__':
    friend_graph = make_a_friends_graph()
    print(friend_graph)
    print(is_there_a_doctor(friend_graph))
