from fractions import Fraction

count = int(input())
total = sum((Fraction(line) for line in (input() for _ in range(count))), start=Fraction())

if total.denominator == 1:
    print(total.numerator)
else:
    print(f"{total.numerator}/{total.denominator}")
