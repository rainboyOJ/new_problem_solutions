#!/usr/bin/env python3
import random


PRIMES = [
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
]


def main():
    random.seed()
    p, q = random.sample(PRIMES, 2)
    print(p * q)


if __name__ == "__main__":
    main()
