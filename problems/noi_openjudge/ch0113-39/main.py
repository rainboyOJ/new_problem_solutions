degree = int(input())
coefficients = list(map(int, input().split()))
parts = []

for index, coefficient in enumerate(coefficients):
    exponent = degree - index
    if coefficient == 0:
        continue
    sign = "-" if coefficient < 0 else "+"
    absolute = abs(coefficient)
    if exponent == 0:
        body = str(absolute)
    elif exponent == 1:
        body = ("" if absolute == 1 else str(absolute)) + "x"
    else:
        body = ("" if absolute == 1 else str(absolute)) + f"x^{exponent}"
    parts.append((sign, body))

first_sign, first_body = parts[0]
print(("" if first_sign == "+" else "-") + first_body + "".join(sign + body for sign, body in parts[1:]))
