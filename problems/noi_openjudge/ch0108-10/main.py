row_count, column_count = map(int, input().split())
matrix = [list(map(int, input().split())) for _ in range(row_count)]

for column in zip(*matrix):
    print(*column)
