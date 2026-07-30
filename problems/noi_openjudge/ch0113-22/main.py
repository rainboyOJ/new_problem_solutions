number = int(input())
factor = 2
parts = []

while factor * factor <= number:
    exponent = 0
    while number % factor == 0:
        number //= factor
        exponent += 1
    if exponent:
        parts.append(str(factor) if exponent == 1 else f"{factor}^{exponent}")
    factor += 1
if number > 1:
    parts.append(str(number))

print("*".join(parts))
