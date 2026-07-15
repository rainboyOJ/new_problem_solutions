import sys


data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
unique = sorted(set(data[1:1 + n]))
print(len(unique))
print(*unique)
