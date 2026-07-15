sides = sorted(map(int, input().split()))
a, b, c = sides

if a + b <= c:
    print("Not triangle", end="")
else:
    result = []
    left = a * a + b * b
    right = c * c

    if left == right:
        result.append("Right triangle")
    elif left > right:
        result.append("Acute triangle")
    else:
        result.append("Obtuse triangle")

    if a == b or b == c:
        result.append("Isosceles triangle")
    if a == c:
        result.append("Equilateral triangle")

    print("\n".join(result), end="")
