import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n, needed_pieces = data[:2]
logs = data[2:2 + n]

def enough(length):
    return sum(log // length for log in logs) >= needed_pieces

left, right = 0, max(logs)
while left < right:
    middle = (left + right + 1) // 2
    if enough(middle):
        left = middle
    else:
        right = middle - 1

print(left)
