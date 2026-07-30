import math

x1, y1 = map(float, input().split())
x2, y2 = map(float, input().split())
print(f"{math.hypot(x1 - x2, y1 - y2):.3f}")
