import math


def normalize_zero(value):
    return 0.0 if value == 0 else value


a, b, c = map(float, input().split())
discriminant = b * b - 4 * a * c

if discriminant > 0:
    root1 = (-b + math.sqrt(discriminant)) / (2 * a)
    root2 = (-b - math.sqrt(discriminant)) / (2 * a)
    root1, root2 = max(root1, root2), min(root1, root2)
    print(f"x1={root1:.5f};x2={root2:.5f}")
elif discriminant == 0:
    root = normalize_zero(-b / (2 * a))
    print(f"x1=x2={root:.5f}")
else:
    real_part = normalize_zero(-b / (2 * a))
    imaginary_part = abs(math.sqrt(-discriminant) / (2 * a))
    print(f"x1={real_part:.5f}+{imaginary_part:.5f}i;x2={real_part:.5f}-{imaginary_part:.5f}i")
