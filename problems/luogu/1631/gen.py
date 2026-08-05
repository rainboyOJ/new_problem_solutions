#!/usr/bin/env python3
import random
import sys

def main():
    n = random.randint(1, 100)
    a = sorted(random.sample(range(1, 10**6), n))
    b = sorted(random.sample(range(1, 10**6), n))
    print(n)
    print(*a)
    print(*b)

if __name__ == "__main__":
    main()
