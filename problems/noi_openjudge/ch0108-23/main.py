row_count, column_count = map(int, input().split())
matrix = [list(map(int, input().split())) for _ in range(row_count)]
top, bottom = 0, row_count - 1
left, right = 0, column_count - 1

while top <= bottom and left <= right:
    for column in range(left, right + 1):
        print(matrix[top][column])
    for row in range(top + 1, bottom + 1):
        print(matrix[row][right])
    if top < bottom:
        for column in range(right - 1, left - 1, -1):
            print(matrix[bottom][column])
    if left < right:
        for row in range(bottom - 1, top, -1):
            print(matrix[row][left])
    top, bottom = top + 1, bottom - 1
    left, right = left + 1, right - 1
