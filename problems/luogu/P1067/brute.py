def term(coef, power, first):
    sign = "-" if coef < 0 else ("" if first else "+")
    value = abs(coef)
    if power == 0:
        body = str(value)
    elif power == 1:
        body = ("x" if value == 1 else f"{value}x")
    else:
        body = (f"x^{power}" if value == 1 else f"{value}x^{power}")
    return sign + body


n = int(input())
coefficients = list(map(int, input().split()))
items = [
    (coef, n - i)
    for i, coef in enumerate(coefficients)
    if coef != 0
]
print("".join(term(coef, power, i == 0) for i, (coef, power) in enumerate(items)))
