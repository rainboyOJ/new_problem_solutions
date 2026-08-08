from functools import cache
import sys


@cache
def w(a, b, c):
    if a <= 0 or b <= 0 or c <= 0:
        return 1
    if a > 20 or b > 20 or c > 20:
        return w(20, 20, 20)
    if a < b < c:
        return w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c)
    return w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1)


answers = []
for a, b, c in map(lambda line: tuple(map(int, line.split())), sys.stdin):
    if (a, b, c) == (-1, -1, -1):
        break
    answers.append(f"w({a}, {b}, {c}) = {w(a, b, c)}")
print("\n".join(answers))
