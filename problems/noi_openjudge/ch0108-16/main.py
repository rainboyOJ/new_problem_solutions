row_count, column_count, days = map(int, input().split())
grid = [list(input().strip()) for _ in range(row_count)]
defeated_by = {"R": "P", "S": "R", "P": "S"}

for _ in range(days):
    next_grid = [row[:] for row in grid]
    for row in range(row_count):
        for column in range(column_count):
            winner = defeated_by[grid[row][column]]
            for dx, dy in ((-1, 0), (1, 0), (0, -1), (0, 1)):
                neighbor_row, neighbor_column = row + dx, column + dy
                if 0 <= neighbor_row < row_count and 0 <= neighbor_column < column_count and grid[neighbor_row][neighbor_column] == winner:
                    next_grid[row][column] = winner
                    break
    grid = next_grid

for row in grid:
    print("".join(row))
