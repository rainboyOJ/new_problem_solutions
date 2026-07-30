column_count = int(input())
ciphertext = input().strip()
row_count = len(ciphertext) // column_count
rows = []

for row in range(row_count):
    segment = ciphertext[row * column_count : (row + 1) * column_count]
    rows.append(segment if row % 2 == 0 else segment[::-1])

print("".join(rows[row][column] for column in range(column_count) for row in range(row_count)))
