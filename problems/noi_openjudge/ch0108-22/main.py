order = int(input())
size = 2 * order - 1
magic_square = [[0] * size for _ in range(size)]
row, column = 0, size // 2

for number in range(1, size * size + 1):
    magic_square[row][column] = number
    next_row = (row - 1) % size
    next_column = (column + 1) % size
    if magic_square[next_row][next_column] != 0:
        row = (row + 1) % size
    else:
        row, column = next_row, next_column

for row in magic_square:
    print(*row)
