import sys


input = sys.stdin.buffer.readline
n = int(input())
matrix = [list(map(int, input().split())) for _ in range(n)]
answer = -10**18

for top in range(n):
    column_sum = [0] * n
    for bottom in range(top, n):
        for column, value in enumerate(matrix[bottom]):
            column_sum[column] += value

        best_ending_here = 0
        for value in column_sum:
            best_ending_here = max(value, best_ending_here + value)
            answer = max(answer, best_ending_here)

print(answer)
