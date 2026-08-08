#!/usr/bin/env python3
import random


def sieve(n: int):
    is_comp = [False] * (n + 1)
    primes = []
    for i in range(2, n + 1):
        if not is_comp[i]:
            primes.append(i)
        for p in primes:
            if i * p > n:
                break
            is_comp[i * p] = True
            if i % p == 0:
                break
    return primes


def main():
    random.seed()
    n = random.randint(10, 5000)
    primes = sieve(n)
    q = random.randint(1, min(50, len(primes)))
    print(n, q)
    for _ in range(q):
        print(random.randint(1, len(primes)))


if __name__ == "__main__":
    main()
