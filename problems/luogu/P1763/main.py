import math


numerator, denominator = map(int, input().split())
path = []


def find(term_count):
    best = None

    def dfs(depth, start, a, b):
        nonlocal best
        slots = term_count - depth
        if slots == 1:
            if b % a:
                return
            value = b // a
            if value < start or value > 10**7:
                return
            candidate = path + [value]
            if best is None or candidate[-1] < best[-1]:
                best = candidate
            return

        lower = max(start, (b + a - 1) // a)
        upper = min(10**7, slots * b // a)
        if best is not None:
            upper = min(upper, best[-1] - 1)
        for value in range(lower, upper + 1):
            next_a = a * value - b
            if next_a <= 0:
                continue
            next_b = b * value
            divisor = math.gcd(next_a, next_b)
            path.append(value)
            dfs(depth + 1, value + 1, next_a // divisor, next_b // divisor)
            path.pop()

    dfs(0, 2, numerator, denominator)
    return best


terms = 1
while (answer := find(terms)) is None:
    terms += 1
print(*answer)
