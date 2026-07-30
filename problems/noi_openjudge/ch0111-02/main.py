def function(x: float) -> float:
    return x**5 - 15 * x**4 + 85 * x**3 - 225 * x**2 + 274 * x - 121


left, right = 1.5, 2.4
for _ in range(100):
    middle = (left + right) / 2
    if function(middle) > 0:
        left = middle
    else:
        right = middle

print(f"{(left + right) / 2:.6f}")
