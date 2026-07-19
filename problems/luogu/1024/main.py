a, b, c, d = map(float, input().split())
EPS = 1e-10


def polynomial(x):
    return ((a * x + b) * x + c) * x + d


def is_zero_at(x, value):
    absolute_x = abs(x)
    scale = ((abs(a) * absolute_x + abs(b)) * absolute_x + abs(c)) * absolute_x + abs(d)
    return abs(value) <= EPS * scale


roots = []
for integer in range(-100, 100):
    left, right = float(integer), float(integer + 1)
    left_value, right_value = polynomial(left), polynomial(right)
    left_is_root = is_zero_at(left, left_value)
    right_is_root = is_zero_at(right, right_value)

    if left_is_root:
        roots.append(left)
    elif not right_is_root and left_value * right_value < 0:
        for _ in range(80):
            middle = (left + right) / 2
            middle_value = polynomial(middle)
            if left_value * middle_value <= 0:
                right = middle
            else:
                left = middle
                left_value = middle_value
        roots.append((left + right) / 2)

right_endpoint_value = polynomial(100.0)
if is_zero_at(100.0, right_endpoint_value):
    roots.append(100.0)

roots = [0.0 if abs(root) < 0.0005 else root for root in roots]
print(*(f"{root:.2f}" for root in roots))
