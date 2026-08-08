import sys
from decimal import Decimal, getcontext


getcontext().prec = 60

coefficient_a, coefficient_b, coefficient_c, coefficient_d = map(
    Decimal, sys.stdin.readline().split()
)


def polynomial(x):
    return ((coefficient_a * x + coefficient_b) * x + coefficient_c) * x + coefficient_d


roots = []
for integer in range(-100, 100):
    left = Decimal(integer)
    right = Decimal(integer + 1)
    left_value = polynomial(left)
    right_value = polynomial(right)

    if left_value == 0:
        roots.append(left)
    elif left_value * right_value < 0:
        for _ in range(180):
            middle = (left + right) / 2
            middle_value = polynomial(middle)
            if left_value * middle_value <= 0:
                right = middle
            else:
                left = middle
                left_value = middle_value
        roots.append((left + right) / 2)

if polynomial(Decimal(100)) == 0:
    roots.append(Decimal(100))

roots = [Decimal(0) if abs(root) < Decimal("0.0005") else root for root in roots]
print(*(f"{root:.2f}" for root in roots))
