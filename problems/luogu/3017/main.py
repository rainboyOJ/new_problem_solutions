import sys


input = sys.stdin.buffer.readline
rows, columns, horizontal_parts, vertical_parts = map(int, input().split())
grid = [list(map(int, input().split())) for _ in range(rows)]


def can_guarantee(target):
    column_sum = [0] * columns
    strips = 0
    for row in grid:
        for j, value in enumerate(row):
            column_sum[j] += value

        pieces = current = 0
        for value in column_sum:
            current += value
            if current >= target:
                pieces += 1
                current = 0

        if pieces >= vertical_parts:
            strips += 1
            column_sum = [0] * columns
    return strips >= horizontal_parts


left, right = 0, sum(map(sum, grid)) // (horizontal_parts * vertical_parts) + 1
while left + 1 < right:
    middle = (left + right) // 2
    if can_guarantee(middle):
        left = middle
    else:
        right = middle
print(left)
