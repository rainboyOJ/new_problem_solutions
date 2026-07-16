import sys


data = sys.stdin.buffer.read().split()
words = set(data[1:])
print(max(sum(word[:length] in words for length in range(1, len(word) + 1))
          for word in words))
