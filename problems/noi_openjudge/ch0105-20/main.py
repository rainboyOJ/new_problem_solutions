from decimal import Decimal, ROUND_HALF_UP


def format_six_significant(value):
    if value == 0:
        return "0"
    quantum = Decimal(1).scaleb(value.adjusted() - 5)
    rounded = value.quantize(quantum, rounding=ROUND_HALF_UP)
    text = format(rounded, "f")
    return text.rstrip("0").rstrip(".") if "." in text else text


height = Decimal(input())
distance = height

for _ in range(9):
    height /= 2
    distance += 2 * height

height /= 2
print(format_six_significant(distance))
print(format_six_significant(height))
