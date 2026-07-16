a, b, c, d = map(float, input().split())


def polynomial(x):
    return ((a * x + b) * x + c) * x + d


roots = []
for integer in range(-100, 100):
    left, right = float(integer), float(integer + 1)
    left_value, right_value = polynomial(left), polynomial(right)

    if abs(left_value) < 1e-10:
        roots.append(left)
    elif left_value * right_value < 0:
        for _ in range(60):
            middle = (left + right) / 2
            if polynomial(left) * polynomial(middle) <= 0:
                right = middle
            else:
                left = middle
        roots.append((left + right) / 2)

if abs(polynomial(100)) < 1e-10:
    roots.append(100.0)

roots = [0.0 if abs(root) < 0.0005 else root for root in roots[:3]]
print(*(f"{root:.2f}" for root in roots))
