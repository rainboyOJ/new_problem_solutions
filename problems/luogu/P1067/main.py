def format_term(coefficient, power, is_first):
    sign = ""
    if coefficient < 0:
        sign = "-"
    elif not is_first:
        sign = "+"

    absolute = abs(coefficient)

    if power == 0:
        body = str(absolute)
    else:
        if absolute == 1:
            body = ""
        else:
            body = str(absolute)

        if power == 1:
            body += "x"
        else:
            body += f"x^{power}"

    return sign + body


n = int(input())
coefficients = list(map(int, input().split()))
terms = []

for index, coefficient in enumerate(coefficients):
    power = n - index
    if coefficient == 0:
        continue
    terms.append(format_term(coefficient, power, not terms))

print("".join(terms))
