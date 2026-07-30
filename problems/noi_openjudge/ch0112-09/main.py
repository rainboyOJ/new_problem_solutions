row_count, column_count = map(int, input().split())
image = [input().split() for _ in range(row_count)]
operations = input()

for operation in operations:
    if operation == "A":
        image = [list(row) for row in zip(*image[::-1])]
    elif operation == "B":
        image = [list(row) for row in zip(*image)][::-1]
    elif operation == "C":
        image = [row[::-1] for row in image]
    else:
        image = image[::-1]

for row in image:
    print(*row)
