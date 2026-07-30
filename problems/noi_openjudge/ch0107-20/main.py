word = input().strip()

for suffix in ("er", "ly", "ing"):
    if word.endswith(suffix):
        word = word[: -len(suffix)]
        break

print(word)
