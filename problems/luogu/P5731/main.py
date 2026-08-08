n = int(input())

matrix = [[0 for _ in range(n)] for _ in range(n)]
directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

row = 0
col = 0
direction = 0

for value in range(1, n * n + 1):
    matrix[row][col] = value

    dr, dc = directions[direction]
    next_row = row + dr
    next_col = col + dc

    if not (0 <= next_row < n and 0 <= next_col < n) or matrix[next_row][next_col] != 0:
        direction = (direction + 1) % 4
        dr, dc = directions[direction]
        next_row = row + dr
        next_col = col + dc

    row, col = next_row, next_col

for line in matrix:
    print("".join(f"{value:3d}" for value in line))
