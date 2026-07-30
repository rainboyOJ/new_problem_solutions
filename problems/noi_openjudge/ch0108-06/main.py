row_count, column_count = map(int, input().split())
first_image = [input().split() for _ in range(row_count)]
same_count = 0

for row in range(row_count):
    second_row = input().split()
    same_count += sum(left == right for left, right in zip(first_image[row], second_row))

print(f"{same_count * 100 / (row_count * column_count):.2f}")
