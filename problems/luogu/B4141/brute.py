import sys
import math
from itertools import combinations

data = sys.stdin.buffer.read().split()
n = int(data[0])

is_prime = [True] * (n + 1)
is_prime[0] = is_prime[1] = False
for p in range(2, int(n ** 0.5) + 1):
    if is_prime[p]:
        for q in range(p * p, n + 1, p):
            is_prime[q] = False
primes = [p for p in range(2, n + 1) if is_prime[p]]

best = 0
for r in range(len(primes), 0, -1):
    found = False
    for combo in combinations(primes, r):
        if sum(combo) == n:
            best = r
            found = True
            break
    if found:
        break

print(best)
