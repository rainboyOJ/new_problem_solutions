import sys
from itertools import accumulate


input = sys.stdin.buffer.readline
n, m, side = map(int, input().split())
prefix = [[0] * (m + 1)]

for _ in range(n):
    row_prefix = accumulate(map(int, input().split()), initial=0)
    prefix.append([up + left for up, left in zip(prefix[-1], row_prefix)])

answer = float("-inf")
answer_x = answer_y = 1

for x in range(n - side + 1):
    for y in range(m - side + 1):
        total = (prefix[x + side][y + side] - prefix[x][y + side]
                 - prefix[x + side][y] + prefix[x][y])
        if total > answer:
            answer = total
            answer_x, answer_y = x + 1, y + 1

print(answer_x, answer_y)
