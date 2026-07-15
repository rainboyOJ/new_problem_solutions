def rotate_square(top, left, size, clockwise):
    block = [row[left:left + size] for row in grid[top:top + size]]

    if clockwise:
        rotated = [
            [block[size - 1 - col][row] for col in range(size)]
            for row in range(size)
        ]
    else:
        rotated = [
            [block[col][size - 1 - row] for col in range(size)]
            for row in range(size)
        ]

    for row in range(size):
        grid[top + row][left:left + size] = rotated[row]


n, m = map(int, input().split())
grid = []
value = 1

for _ in range(n):
    row = []
    for _ in range(n):
        row.append(value)
        value += 1
    grid.append(row)

for _ in range(m):
    x, y, r, z = map(int, input().split())
    size = 2 * r + 1
    top = x - r - 1
    left = y - r - 1
    rotate_square(top, left, size, z == 0)

for row in grid:
    print(*row)
