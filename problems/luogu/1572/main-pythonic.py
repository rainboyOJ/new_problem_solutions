import re
from fractions import Fraction

expression = input().strip()
result = sum(map(Fraction, re.findall(r"[+-]?\d+/\d+", expression)), Fraction())
print(result.numerator if result.denominator == 1 else result)
