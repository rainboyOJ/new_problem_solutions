import sys


input = sys.stdin.buffer.readline
n = int(input())
matrix = [list(map(int, input().split())) for _ in range(n)]
answer = float("-inf")

for top in range(n):
    column_sum = [0] * n
    for row in matrix[top:]:
        column_sum = [x + y for x, y in zip(column_sum, row)]

        current = 0
        for value in column_sum:
            current = max(current, 0) + value
            answer = max(answer, current)

print(answer)
