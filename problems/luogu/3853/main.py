import sys
from itertools import pairwise


data = list(map(int, sys.stdin.buffer.read().split()))
length, n, limit = data[:3]
signs = data[3:3 + n]
gaps = [right - left for left, right in pairwise(signs)]


def possible(maximum_gap):
    needed = sum((gap - 1) // maximum_gap for gap in gaps)
    return needed <= limit


left, right = 1, max(gaps)
while left < right:
    middle = (left + right) // 2
    if possible(middle):
        right = middle
    else:
        left = middle + 1

print(left)
