from functools import cmp_to_key
from itertools import permutations
import sys


def compare(x, y):
    return -1 if x + y > y + x else (1 if x + y < y + x else 0)


tokens = sys.stdin.read().split()
n = int(tokens[0])
numbers = tokens[1:1 + n]

if n > 8:
    numbers.sort(key=cmp_to_key(compare))
    print("".join(numbers))
else:
    print(max("".join(order) for order in permutations(numbers)))
