row_count, column_count = map(int, input().split())
field = [input().strip() for _ in range(row_count)]
directions = ((-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1))

for row in range(row_count):
    output = []
    for column in range(column_count):
        if field[row][column] == "*":
            output.append("*")
            continue
        mines = sum(0 <= row + dx < row_count and 0 <= column + dy < column_count and field[row + dx][column + dy] == "*" for dx, dy in directions)
        output.append(str(mines))
    print("".join(output))
