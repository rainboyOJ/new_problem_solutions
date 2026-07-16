import sys


data = list(map(int, sys.stdin.buffer.read().split()))
n, need = data[:2]
heights = data[2:2 + n]


def enough(cut):
    return sum(max(0, height - cut) for height in heights) >= need


left, right = 0, max(heights)
while left < right:
    middle = (left + right + 1) // 2
    if enough(middle):
        left = middle
    else:
        right = middle - 1

print(left)
