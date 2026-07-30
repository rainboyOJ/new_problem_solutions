row_count, column_count = map(int, input().split())
matrix = [list(map(int, input().split())) for _ in range(row_count)]

for diagonal in range(row_count + column_count - 1):
    row = 0 if diagonal < column_count else diagonal - column_count + 1
    column = diagonal if diagonal < column_count else column_count - 1
    while row < row_count and column >= 0:
        print(matrix[row][column])
        row += 1
        column -= 1
