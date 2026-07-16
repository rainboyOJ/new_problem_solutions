import math
import random
import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n, group_limit = next(data), next(data)
points = [(next(data), next(data)) for _ in range(n)]
cache = {}


def diameter_circle(a, b):
    center_x = (a[0] + b[0]) / 2
    center_y = (a[1] + b[1]) / 2
    radius = math.hypot(a[0] - b[0], a[1] - b[1]) / 2
    return center_x, center_y, radius


def circumcircle(a, b, c):
    ax, ay = a
    bx, by = b
    cx, cy = c
    denominator = 2 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by))
    if abs(denominator) < 1e-18:
        pairs = ((a, b), (a, c), (b, c))
        return diameter_circle(*max(pairs, key=lambda pair:
            (pair[0][0] - pair[1][0]) ** 2 + (pair[0][1] - pair[1][1]) ** 2))
    a2 = ax * ax + ay * ay
    b2 = bx * bx + by * by
    c2 = cx * cx + cy * cy
    center_x = (a2 * (by - cy) + b2 * (cy - ay) + c2 * (ay - by)) / denominator
    center_y = (a2 * (cx - bx) + b2 * (ax - cx) + c2 * (bx - ax)) / denominator
    return center_x, center_y, math.hypot(center_x - ax, center_y - ay)


def minimum_circle(left, right):
    key = (left, right)
    circle = cache.get(key)
    if circle is not None:
        return circle
    selected = points[left:right]
    if len(selected) == 1:
        circle = selected[0][0], selected[0][1], 0.0
    elif len(selected) == 2:
        circle = diameter_circle(*selected)
    else:
        random.Random(left * 1000003 + right).shuffle(selected)
        center_x, center_y = selected[0]
        radius = 0.0
        for i, point in enumerate(selected):
            if math.hypot(point[0] - center_x, point[1] - center_y) <= radius + 1e-9:
                continue
            center_x, center_y = point
            radius = 0.0
            for j in range(i):
                other = selected[j]
                if math.hypot(other[0] - center_x, other[1] - center_y) <= radius + 1e-9:
                    continue
                center_x, center_y, radius = diameter_circle(point, other)
                for third in selected[:j]:
                    if math.hypot(third[0] - center_x, third[1] - center_y) > radius + 1e-9:
                        center_x, center_y, radius = circumcircle(point, other, third)
        circle = center_x, center_y, radius
    if len(cache) < 250000:
        cache[key] = circle
    return circle


def partition(limit, keep_segments=False):
    segments = []
    left = 0
    while left < n:
        length = 1
        while (left + 2 * length <= n
               and minimum_circle(left, left + 2 * length)[2] <= limit + 1e-8):
            length *= 2
        low = left + length
        high = min(n, left + 2 * length)
        while low < high:
            middle = (low + high + 1) // 2
            if minimum_circle(left, middle)[2] <= limit + 1e-8:
                low = middle
            else:
                high = middle - 1
        segments.append((left, low))
        if len(segments) > group_limit:
            return None
        left = low
    return segments if keep_segments else True


low = 0.0
high = minimum_circle(0, n)[2]
for _ in range(48):
    middle = (low + high) / 2
    if partition(middle):
        high = middle
    else:
        low = middle

segments = partition(high + 1e-7, True)
print(f"{high + 1e-7:.10f}")
print(len(segments))
for left, right in segments:
    center_x, center_y, _ = minimum_circle(left, right)
    print(f"{center_x:.10f} {center_y:.10f}")
