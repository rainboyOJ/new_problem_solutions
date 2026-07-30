number = int(input())
sign = "-" if number < 0 else ""
reversed_digits = str(abs(number))[::-1].lstrip("0") or "0"
print(sign + reversed_digits)
