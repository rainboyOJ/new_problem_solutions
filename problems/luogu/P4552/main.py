import sys
from itertools import pairwise


data = iter(map(int, sys.stdin.buffer.read().split()))
n = next(data)
sequence = [next(data) for _ in range(n)]
positive = sum(max(0, right - left) for left, right in pairwise(sequence))
negative = sum(max(0, left - right) for left, right in pairwise(sequence))
print(max(positive, negative))
print(abs(positive - negative) + 1)
