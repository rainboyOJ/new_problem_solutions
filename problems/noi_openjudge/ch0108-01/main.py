matrix = [input().split() for _ in range(5)]
first_row, second_row = map(int, input().split())
matrix[first_row - 1], matrix[second_row - 1] = matrix[second_row - 1], matrix[first_row - 1]

for row in matrix:
    print(*row)
