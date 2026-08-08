word = input().strip().lower()
article = input().rstrip("\n").lower()

padded_article = " " + article + " "
padded_word = " " + word + " "

first_position = padded_article.find(padded_word)

if first_position == -1:
    print(-1)
else:
    print(padded_article.count(padded_word), first_position)
