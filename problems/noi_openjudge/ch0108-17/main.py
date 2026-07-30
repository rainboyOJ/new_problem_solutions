from collections import deque

row_count, column_count = map(int, input().split())
field = [list(input().strip()) for _ in range(row_count)]
clump_count = 0

for row in range(row_count):
    for column in range(column_count):
        if field[row][column] != "#":
            continue
        clump_count += 1
        field[row][column] = "."
        queue = deque([(row, column)])
        while queue:
            current_row, current_column = queue.popleft()
            for dx, dy in ((-1, 0), (1, 0), (0, -1), (0, 1)):
                next_row, next_column = current_row + dx, current_column + dy
                if 0 <= next_row < row_count and 0 <= next_column < column_count and field[next_row][next_column] == "#":
                    field[next_row][next_column] = "."
                    queue.append((next_row, next_column))

print(clump_count)
