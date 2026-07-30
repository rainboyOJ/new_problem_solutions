matrix = [list(map(int, input().split())) for _ in range(5)]

for row, values in enumerate(matrix):
    value = max(values)
    column = values.index(value)
    if value == min(matrix[index][column] for index in range(5)):
        print(row + 1, column + 1, value)
        break
else:
    print("not found")
