word = input().strip().lower()
article = input().rstrip("\n").lower()

padded_article = " " + article + " "
padded_word = " " + word + " "

first_position = padded_article.find(padded_word)

if first_position == -1:
    print(-1)
else:
    # 逐步 find 统计次数：str.count 按不重叠匹配计数，对单字母单词（如 " a a "）会漏数
    count_match = 0
    pos = first_position
    while pos != -1:
        count_match += 1
        pos = padded_article.find(padded_word, pos + 1)
    print(count_match, first_position)
