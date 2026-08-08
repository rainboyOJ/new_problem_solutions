#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 8)
    m = random.randint(1, 8)
    d = [random.randint(0, 5) for _ in range(n - 1)]
    total = sum(d)
    k = random.randint(0, min(5, total))

    print(n, m, k)
    print(*d)
    for _ in range(m):
        a = random.randint(1, n - 1)
        b = random.randint(a + 1, n)
        t = random.randint(0, 12)
        print(t, a, b)


if __name__ == "__main__":
    main()
