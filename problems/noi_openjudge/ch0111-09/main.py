from math import asin, sqrt

length, temperature_change, coefficient = map(float, input().split())
expanded_length = length * (1 + temperature_change * coefficient)

if expanded_length == length:
    print("0.000")
else:
    # 半径越大，对应的圆弧越接近弦，弧长越小。
    low, high = length / 2, 1e18
    for _ in range(200):
        radius = (low + high) / 2
        arc_length = 2 * radius * asin(length / (2 * radius))
        if arc_length > expanded_length:
            low = radius
        else:
            high = radius
    radius = (low + high) / 2
    offset = radius - sqrt(radius * radius - (length / 2) ** 2)
    print(f"{offset:.3f}")
