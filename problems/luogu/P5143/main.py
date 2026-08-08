import math
import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]

points = []
index = 1
for _ in range(n):
    x = data[index]
    y = data[index + 1]
    z = data[index + 2]
    points.append((z, x, y))
    index += 3

points.sort()

distance = 0.0
for i in range(n - 1):
    z1, x1, y1 = points[i]
    z2, x2, y2 = points[i + 1]
    distance += math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2 + (z1 - z2) ** 2)

print(f"{distance:.3f}")
