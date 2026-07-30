row_text, column_text, message = input().split(" ", 2)
row_count = int(row_text)
column_count = int(column_text)
bits = "".join(f"{0 if character == ' ' else ord(character) - ord('A') + 1:05b}" for character in message)
bits += "0" * (row_count * column_count - len(bits))
matrix = [["0"] * column_count for _ in range(row_count)]
index = 0
top, bottom = 0, row_count - 1
left, right = 0, column_count - 1

while top <= bottom and left <= right:
    for column in range(left, right + 1):
        matrix[top][column] = bits[index]
        index += 1
    for row in range(top + 1, bottom + 1):
        matrix[row][right] = bits[index]
        index += 1
    if top < bottom:
        for column in range(right - 1, left - 1, -1):
            matrix[bottom][column] = bits[index]
            index += 1
    if left < right:
        for row in range(bottom - 1, top, -1):
            matrix[row][left] = bits[index]
            index += 1
    top, bottom = top + 1, bottom - 1
    left, right = left + 1, right - 1

print("".join("".join(row) for row in matrix))
