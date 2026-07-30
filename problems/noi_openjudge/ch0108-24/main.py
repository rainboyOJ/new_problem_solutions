size = int(input())
matrix = [[0] * size for _ in range(size)]
number = 1

for diagonal in range(2 * size - 1):
    row_start = max(0, diagonal - size + 1)
    row_end = min(size - 1, diagonal)
    rows = range(row_start, row_end + 1)
    if diagonal % 2 == 0:
        rows = reversed(list(rows))
    for row in rows:
        column = diagonal - row
        matrix[row][column] = number
        number += 1

for row in matrix:
    print(*row)
