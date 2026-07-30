initial_count, days = map(int, input().split())
current = [[0] * 9 for _ in range(9)]
current[4][4] = initial_count

for _ in range(days):
    following = [[0] * 9 for _ in range(9)]
    for row in range(9):
        for column in range(9):
            count = current[row][column]
            if count == 0:
                continue
            following[row][column] += 2 * count
            for dx in (-1, 0, 1):
                for dy in (-1, 0, 1):
                    if (dx, dy) != (0, 0):
                        following[row + dx][column + dy] += count
    current = following

for row in current:
    print(*row)
