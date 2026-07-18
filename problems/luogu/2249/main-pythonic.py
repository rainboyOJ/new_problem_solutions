import sys
from bisect import bisect_left

data = list(map(int, sys.stdin.buffer.read().split()))
n, m = data[:2]
numbers = data[2:2 + n]
queries = data[2 + n:2 + n + m]

def first_position(value):
    index = bisect_left(numbers, value)
    return index + 1 if index < n and numbers[index] == value else -1

print(*map(first_position, queries))
