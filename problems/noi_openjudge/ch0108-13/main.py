row_count, column_count = map(int, input().split())
image = [list(map(int, input().split())) for _ in range(row_count)]
blurred = [row[:] for row in image]

for row in range(1, row_count - 1):
    for column in range(1, column_count - 1):
        total = image[row][column] + image[row - 1][column] + image[row + 1][column] + image[row][column - 1] + image[row][column + 1]
        blurred[row][column] = (total + 2) // 5

for row in blurred:
    print(*row)
