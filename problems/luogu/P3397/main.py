import sys


input = sys.stdin.buffer.readline
n, m = map(int, input().split())
difference = [[0] * (n + 2) for _ in range(n + 2)]

for _ in range(m):
    x1, y1, x2, y2 = map(int, input().split())
    difference[x1][y1] += 1
    difference[x1][y2 + 1] -= 1
    difference[x2 + 1][y1] -= 1
    difference[x2 + 1][y2 + 1] += 1

for i in range(1, n + 1):
    row_sum = 0
    row, previous_row = difference[i], difference[i - 1]
    for j in range(1, n + 1):
        row_sum += row[j]
        row[j] = row_sum + previous_row[j]

print("\n".join(
    " ".join(map(str, row[1:n + 1]))
    for row in difference[1:n + 1]
))
