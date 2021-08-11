# O(n²)

# 任务：游戏分数排名
# 创建一个字典
player_name_list = ["Bob", "Alex", "Kath", "Dov", "Jack"]
player_score_list = [70, 89, 54, 99, 80]
player_info = {}
for i in range(len(player_name_list)):
    player_info[player_name_list[i]] = player_score_list[i]
print(player_info)

# 比较
ranking_list = []
while player_info:
    high_score = 0
    target_player = ""
    for player in player_info:
        if player_info[player] > high_score:
            target_player = player
            high_score = player_info[player]
    player_info.pop(target_player)
    ranking_list.append(target_player)

print(ranking_list)
