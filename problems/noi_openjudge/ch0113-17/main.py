import sys

tokens = sys.stdin.read().split()
word_count = int(tokens[0])
words = tokens[1 : word_count + 1]
line = ""

for word in words:
    if not line:
        line = word
    elif len(line) + 1 + len(word) <= 80:
        line += " " + word
    else:
        print(line)
        line = word
print(line)
