from math import gcd
import sys


def read_all_ints():
    return list(map(int, sys.stdin.buffer.read().split()))


sides = sorted(read_all_ints())
g = gcd(sides[0], sides[2])
print(f"{sides[0] // g}/{sides[2] // g}", end="")
