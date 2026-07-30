from decimal import Decimal, getcontext

getcontext().prec = 60
octal_number = input()
fractional_digits = octal_number.split(".")[1]
numerator = int(fractional_digits, 8)
value = Decimal(numerator) / (Decimal(8) ** len(fractional_digits))
decimal_number = format(value, "f").rstrip("0")

print(f"{octal_number} [8] = {decimal_number} [10]")
