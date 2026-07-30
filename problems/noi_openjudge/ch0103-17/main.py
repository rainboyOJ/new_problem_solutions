x1, y1, x2, y2, x3, y3 = map(float, input().split())
twice_area = x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2
print(f"{abs(twice_area) / 2:.2f}")
