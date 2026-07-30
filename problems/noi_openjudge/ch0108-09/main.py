row_count, shared_count, column_count = map(int, input().split())
first = [list(map(int, input().split())) for _ in range(row_count)]
second = [list(map(int, input().split())) for _ in range(shared_count)]

for row in first:
    print(*(sum(row[index] * second[index][column] for index in range(shared_count)) for column in range(column_count)))
