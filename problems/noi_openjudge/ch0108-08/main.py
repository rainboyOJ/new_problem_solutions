row_count, column_count = map(int, input().split())
first = [list(map(int, input().split())) for _ in range(row_count)]

for row in first:
    second_row = map(int, input().split())
    print(*(left + right for left, right in zip(row, second_row)))
