#!/usr/bin/env python3
import random

def main():
    random.seed()
    n = random.randint(2, 8)
    q = random.randint(1, 10)
    print(n, q)
    print(*[random.randint(1, 2**10) for _ in range(n)])
    for i in range(2, n + 1):
        print(i, random.randint(1, i - 1))
    for _ in range(q):
        if random.random() < 0.5:
            print(1, random.randint(1, n), random.randint(1, 2**10))
        else:
            print(2, random.randint(1, n), random.randint(1, n), random.randint(1, 2**10))

if __name__ == "__main__":
    main()
