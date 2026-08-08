from math import isqrt


def is_prime(x):
    if x < 2:
        return False
    if x == 2:
        return True
    if x % 2 == 0:
        return False

    for d in range(3, isqrt(x) + 1, 2):
        if x % d == 0:
            return False
    return True


limit = int(input())

total = 0
candidate = 2
primes = []

while total + candidate <= limit:
    if is_prime(candidate):
        total += candidate
        primes.append(str(candidate))
    candidate += 1

primes.append(str(len(primes)))
print("\n".join(primes))
