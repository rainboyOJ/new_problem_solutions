import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
numbers = data[1:1 + n]
numbers.sort()
print(*numbers)
