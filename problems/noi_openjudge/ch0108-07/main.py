size = int(input())
matrix = [list(map(int, input().split())) for _ in range(size)]

while len(matrix) > 1:
    print(matrix[1][1])

    for row in matrix:
        minimum = min(row)
        for column in range(len(row)):
            row[column] -= minimum

    for column in range(len(matrix)):
        minimum = min(row[column] for row in matrix)
        for row in matrix:
            row[column] -= minimum

    matrix = [row[:1] + row[2:] for row in matrix[:1] + matrix[2:]]

print(0)
