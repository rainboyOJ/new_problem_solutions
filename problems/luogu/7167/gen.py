#!/usr/bin/env python3
import random

def main():
    random.seed()
    n = random.randint(2, 30)
    q = random.randint(1, 20)
    print(n, q)
    for _ in range(n):
        print(random.randint(1, 50), random.randint(1, 10))
    for _ in range(q):
        print(random.randint(1, n), random.randint(1, 200))

if __name__ == "__main__":
    main()
