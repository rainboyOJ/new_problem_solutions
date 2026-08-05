#!/usr/bin/env python3
import random

def main():
    random.seed()
    n = random.randint(1, 8)
    m = random.randint(1, 8)
    q = random.randint(1, 8)
    print(n, m, q)
    for _ in range(n):
        print(*[random.randint(1, 4) for _ in range(m)])
    for _ in range(q):
        print(random.randint(1, n), random.randint(1, m))

if __name__ == "__main__":
    main()
