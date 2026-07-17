n = int(input())
triangle = [[1]]
for row in range(1, n):
    prev = triangle[-1]
    triangle.append([1] + [prev[i] + prev[i + 1] for i in range(row - 1)] + [1])
for row in triangle:
    print(*row)
