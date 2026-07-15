from math import sqrt

a, b, c = map(float, input().split())
p = (a + b + c) / 2
area = sqrt(p * (p - a) * (p - b) * (p - c))

print(f"{area:.1f}", end="")
