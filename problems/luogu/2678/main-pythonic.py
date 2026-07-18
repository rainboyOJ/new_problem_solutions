import sys

data = list(map(int, sys.stdin.buffer.read().split()))
length, n, limit = data[:3]
stones = data[3:3 + n] + [length]

def possible(distance):
    removed = 0
    previous = 0
    for position in stones:
        if position - previous < distance:
            removed += 1
        else:
            previous = position
    return removed <= limit

left, right = 0, length
while left < right:
    middle = (left + right + 1) // 2
    if possible(middle):
        left = middle
    else:
        right = middle - 1

print(left)
