#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 18)
    m = random.randint(1, n)
    print(n, m)
    print(" ".join(str(random.randint(1, 30)) for _ in range(n)))
    if n > 1:
        print(" ".join(str(random.randint(1, i - 1)) for i in range(2, n + 1)))
    for _ in range(m):
        print(random.randint(1, n))


if __name__ == "__main__":
    main()
