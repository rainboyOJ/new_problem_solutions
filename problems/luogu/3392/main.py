n, m = map(int, input().split())
grid = [input().strip() for _ in range(n)]

colors = "WBR"
cost = [[0] * 3 for _ in range(n)]

for row in range(n):
    for color_index, color in enumerate(colors):
        cost[row][color_index] = sum(cell != color for cell in grid[row])

prefix = [[0] * (n + 1) for _ in range(3)]
for color_index in range(3):
    for row in range(n):
        prefix[color_index][row + 1] = prefix[color_index][row] + cost[row][color_index]

answer = n * m
for white_end in range(1, n - 1):
    for blue_end in range(white_end + 1, n):
        current = (
            prefix[0][white_end]
            + prefix[1][blue_end] - prefix[1][white_end]
            + prefix[2][n] - prefix[2][blue_end]
        )
        answer = min(answer, current)

print(answer)
