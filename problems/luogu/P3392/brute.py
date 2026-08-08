import sys


input = sys.stdin.buffer.readline
n, m = map(int, input().split())
grid = [input().decode().strip() for _ in range(n)]

def repaint_cost(rows, color):
    return sum(cell != color for row in rows for cell in row)


answer = n * m
for white_end in range(1, n - 1):
    for blue_end in range(white_end + 1, n):
        answer = min(
            answer,
            repaint_cost(grid[:white_end], "W")
            + repaint_cost(grid[white_end:blue_end], "B")
            + repaint_cost(grid[blue_end:], "R"),
        )
print(answer)
