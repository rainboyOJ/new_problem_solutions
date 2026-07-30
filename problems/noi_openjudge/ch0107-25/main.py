words = input().replace(",", " ").split()
print(max(words, key=len))
print(min(words, key=len))
