from math import isqrt
import sys


def is_prime(x):
    if x < 2:
        return False
    for d in range(2, isqrt(x) + 1):
        if x % d == 0:
            return False
    return True


def is_palindrome(x):
    s = str(x)
    return s == s[::-1]


def read_all_ints():
    return list(map(int, sys.stdin.buffer.read().split()))


a, b = read_all_ints()
answer = []
for x in range(a, b + 1):
    if is_palindrome(x) and is_prime(x):
        answer.append(str(x))
print("\n".join(answer))
