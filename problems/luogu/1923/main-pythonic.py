import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
k = data[1]
numbers = data[2:2 + n]
numbers.sort()

print(numbers[k])
