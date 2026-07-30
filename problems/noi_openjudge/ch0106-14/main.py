import math
import sys

if hasattr(sys, "set_int_max_str_digits"):
    sys.set_int_max_str_digits(0)

number = int(input())
print(math.factorial(number))
