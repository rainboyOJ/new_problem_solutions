x, a, b, c, d = map(float, input().split())
value = ((a * x + b) * x + c) * x + d
print(f"{value:.7f}")
