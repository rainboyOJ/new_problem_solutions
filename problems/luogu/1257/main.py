import heapq
import math
import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n = next(data)
points = sorted((next(data), next(data)) for _ in range(n))


def closest(left, right):
    length = right - left
    if length <= 3:
        best = math.inf
        for i in range(left, right):
            for j in range(i + 1, right):
                dx = points[i][0] - points[j][0]
                dy = points[i][1] - points[j][1]
                best = min(best, dx * dx + dy * dy)
        return sorted(points[left:right], key=lambda point: point[1]), best

    middle = (left + right) // 2
    middle_x = points[middle][0]
    left_y, left_best = closest(left, middle)
    right_y, right_best = closest(middle, right)
    best = min(left_best, right_best)
    ordered_y = list(heapq.merge(left_y, right_y, key=lambda point: point[1]))
    strip = [point for point in ordered_y if (point[0] - middle_x) ** 2 < best]
    for i, (x1, y1) in enumerate(strip):
        for x2, y2 in strip[i + 1:i + 8]:
            if (y2 - y1) ** 2 >= best:
                break
            best = min(best, (x2 - x1) ** 2 + (y2 - y1) ** 2)
    return ordered_y, best


_, distance_squared = closest(0, n)
print(f"{math.sqrt(distance_squared):.4f}")
