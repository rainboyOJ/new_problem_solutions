a, b = map(float, input().split())
remainder = a - int(a / b) * b
print(f"{remainder:g}")
