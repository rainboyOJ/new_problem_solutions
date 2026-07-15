n = int(input())

square = [[0 for _ in range(n)] for _ in range(n)]

row = 0
col = n // 2

for value in range(1, n * n + 1):
    square[row][col] = value

    next_row = (row - 1) % n
    next_col = (col + 1) % n

    if square[next_row][next_col] == 0:
        row, col = next_row, next_col
    else:
        row += 1

for line in square:
    print(*line)
