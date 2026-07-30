row_count, column_count = map(int, input().split())
image = [input().split() for _ in range(row_count)]

for column in range(column_count):
    print(*(image[row][column] for row in range(row_count - 1, -1, -1)))
