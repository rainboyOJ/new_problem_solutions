#!/usr/bin/env python3
import random

def main():
    random.seed()
    m = random.randint(2, 5)
    n = random.randint(2, 5)
    print(m, n)
    for _ in range(m):
        print(*[random.randint(0, 1) for _ in range(n)])
    print(random.randint(1, m), random.randint(1, n))
    print(random.randint(1, m), random.randint(1, n))

if __name__ == "__main__":
    main()
