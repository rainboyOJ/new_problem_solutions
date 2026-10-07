#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 6)
    m = random.randint(1, 6)
    print(n, m)
    for _ in range(n):
        print(*[random.randint(1, 50) for _ in range(m)])
    print(random.randint(1, n), random.randint(1, m))


if __name__ == "__main__":
    main()
