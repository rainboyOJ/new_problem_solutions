import sys
from array import array


input = sys.stdin.buffer.readline
n, m, side = map(int, input().split())
prefix = [array("q", [0]) * (m + 1) for _ in range(n + 1)]

for i in range(1, n + 1):
    row_sum = 0
    previous_row, row = prefix[i - 1], prefix[i]
    for j, value in enumerate(map(int, input().split()), 1):
        row_sum += value
        row[j] = previous_row[j] + row_sum

answer = -10**30
answer_position = (1, 1)
for bottom in range(side, n + 1):
    top = bottom - side
    for right in range(side, m + 1):
        left = right - side
        total = (prefix[bottom][right] - prefix[top][right]
                 - prefix[bottom][left] + prefix[top][left])
        if total > answer:
            answer = total
            answer_position = (top + 1, left + 1)

print(*answer_position)
