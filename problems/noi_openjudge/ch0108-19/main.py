size = int(input())
image = [list(map(int, input().split())) for _ in range(size)]
area = 0
perimeter = 0

for row in range(size):
    for column in range(size):
        if image[row][column] > 50:
            continue
        area += 1
        if row in (0, size - 1) or column in (0, size - 1) or any(image[row + dx][column + dy] > 50 for dx, dy in ((-1, 0), (1, 0), (0, -1), (0, 1)) if 0 <= row + dx < size and 0 <= column + dy < size):
            perimeter += 1

print(area, perimeter)
