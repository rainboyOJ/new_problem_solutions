n = int(input())

triangle = []

for row in range(n):
    current = [1] * (row + 1)
    for col in range(1, row):
        current[col] = triangle[row - 1][col - 1] + triangle[row - 1][col]
    triangle.append(current)

for row in triangle:
    print(*row)
