# 任务：英语单词排序器
from random import randint


def create_words():
    # 创建许多随机单词
    list_of_words = []
    number_of_word = randint(5000, 5880)
    for i in range(number_of_word):
        length_of_word = randint(1, 8)
        word = ""
        for n in range(length_of_word):
            number_of_character = randint(97, 122)
            character = chr(number_of_character)
            word += character
        list_of_words.append(word)
    return list_of_words


def deal_word(word):
    # 处理单词
    final_list.append(word)
    to_deal_list.remove(word)


def find_word(word_list):
    # 找出最靠前的单词
    ready_to_deal_list = []
    ready_to_deal_list.extend(word_list)
    temporary_list = []
    i = 0
    while len(ready_to_deal_list) != 1:
        compare = "z"
        for word in ready_to_deal_list:
            if len(word) == i:
                temporary_list.clear()
                temporary_list.append(word)
                break
            elif word[i] < compare:
                temporary_list.clear()
                temporary_list.append(word)
                compare = word[i]
            elif word[i] == compare:
                temporary_list.append(word)
                compare = word[i]
        ready_to_deal_list.clear()
        ready_to_deal_list.extend(temporary_list)
        i += 1
    return ready_to_deal_list[0]


if __name__ == '__main__':
    raw_to_deal_list = create_words()
    to_deal_list = list(set(raw_to_deal_list))  # 去掉相同的单词（不去掉也能运行）
    print("排序前：" + str(to_deal_list))

    final_list = []
    while to_deal_list:
        deal_word(find_word(to_deal_list))
    print("排序后：" + str(final_list))
