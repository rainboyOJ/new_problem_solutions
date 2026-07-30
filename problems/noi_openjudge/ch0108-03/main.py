row_count, column_count = map(int, input().split())
total = 0

for row in range(row_count):
    values = list(map(int, input().split()))
    for column, value in enumerate(values):
        if row in (0, row_count - 1) or column in (0, column_count - 1):
            total += value

print(total)
