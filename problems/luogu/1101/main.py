n = int(input())
grid = [input().strip() for _ in range(n)]
word = "yizhong"
marked = [[False] * n for _ in range(n)]
directions = [
    (dx, dy)
    for dx in (-1, 0, 1)
    for dy in (-1, 0, 1)
    if (dx, dy) != (0, 0)
]

for x in range(n):
    for y in range(n):
        for dx, dy in directions:
            positions = [(x + dx * step, y + dy * step) for step in range(7)]
            if all(
                0 <= row < n and 0 <= col < n and grid[row][col] == letter
                for (row, col), letter in zip(positions, word)
            ):
                for row, col in positions:
                    marked[row][col] = True

for row, flags in zip(grid, marked):
    print("".join(letter if keep else "*" for letter, keep in zip(row, flags)))
