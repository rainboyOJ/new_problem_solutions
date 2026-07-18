from math import hypot

def distance(p, q):
    return hypot(p[0] - q[0], p[1] - q[1])

points = [tuple(map(float, input().split())) for _ in range(3)]
perimeter = (
    distance(points[0], points[1])
    + distance(points[1], points[2])
    + distance(points[2], points[0])
)

print(f"{perimeter:.2f}")
