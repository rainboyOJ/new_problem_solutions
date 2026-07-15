word = input().strip().lower()
article = input().rstrip("\n").lower().split()

count = 0
first_word_index = -1
for i, current in enumerate(article):
    if current == word:
        if first_word_index == -1:
            first_word_index = i
        count += 1

if count == 0:
    print(-1)
else:
    position = 0
    for i in range(first_word_index):
        position += len(article[i]) + 1
    print(count, position)
