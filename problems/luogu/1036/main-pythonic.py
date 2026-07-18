from itertools import combinations
from math import isqrt

def is_prime(x):
    if x < 2:
        return False
    for factor in range(2, isqrt(x) + 1):
        if x % factor == 0:
            return False
    return True

n, k = map(int, input().split())
numbers = list(map(int, input().split()))

answer = 0
for chosen in combinations(numbers, k):
    if is_prime(sum(chosen)):
        answer += 1

print(answer)
