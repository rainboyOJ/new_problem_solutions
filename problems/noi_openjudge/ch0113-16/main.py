sentence = input().rstrip(".")
words = sentence.split()

print(max(words, key=len))
