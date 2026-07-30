size = int(input())
matrix = [list(map(int, input().split())) for _ in range(size)]
odd_rows = [index for index, row in enumerate(matrix) if sum(row) % 2]
odd_columns = [index for index in range(size) if sum(matrix[row][index] for row in range(size)) % 2]

if not odd_rows and not odd_columns:
    print("OK")
elif len(odd_rows) == len(odd_columns) == 1:
    print(odd_rows[0] + 1, odd_columns[0] + 1)
else:
    print("Corrupt")
