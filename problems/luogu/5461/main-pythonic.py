def pardon(top, left, size):
    if size == 1:
        return

    half = size // 2

    for row in range(top, top + half):
        for col in range(left, left + half):
            grid[row][col] = 0

    pardon(top, left + half, half)
    pardon(top + half, left, half)
    pardon(top + half, left + half, half)

n = int(input())
size = 2 ** n
grid = [[1 for _ in range(size)] for _ in range(size)]

pardon(0, 0, size)

for row in grid:
    print(*row)
