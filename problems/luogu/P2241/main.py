n, m = map(int, input().split())

square_count = 0
for side in range(1, min(n, m) + 1):
    square_count += (n - side + 1) * (m - side + 1)

all_rectangles = n * (n + 1) * m * (m + 1) // 4
rectangle_count = all_rectangles - square_count

print(square_count, rectangle_count)
