target = input().lower()
article = input().lower()

matches = []
position = 0
for word in article.split(" "):
    if word == target:
        matches.append(position)
    position += len(word) + 1

if matches:
    print(len(matches), matches[0])
else:
    print(-1)
