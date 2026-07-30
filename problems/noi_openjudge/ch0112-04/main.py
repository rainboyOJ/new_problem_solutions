row_count, column_count = map(int, input().split())
matrix = [list(map(int, input().split())) for _ in range(row_count)]
pattern_rows, pattern_columns = map(int, input().split())
pattern = [list(map(int, input().split())) for _ in range(pattern_rows)]

best_position = (0, 0)
best_difference = float("inf")

for top in range(row_count - pattern_rows + 1):
    for left in range(column_count - pattern_columns + 1):
        difference = sum(
            abs(matrix[top + row][left + column] - pattern[row][column])
            for row in range(pattern_rows)
            for column in range(pattern_columns)
        )
        if difference < best_difference:
            best_difference = difference
            best_position = (top, left)

top, left = best_position
for row in matrix[top : top + pattern_rows]:
    print(*row[left : left + pattern_columns])
