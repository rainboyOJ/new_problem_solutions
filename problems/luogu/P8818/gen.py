#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 40)
    m = random.randint(1, 40)
    q = random.randint(1, 60)
    a = [random.randint(-10, 10) for _ in range(n)]
    b = [random.randint(-10, 10) for _ in range(m)]
    print(n, m, q)
    print(*a)
    print(*b)
    for _ in range(q):
        l1 = random.randint(1, n)
        r1 = random.randint(l1, n)
        l2 = random.randint(1, m)
        r2 = random.randint(l2, m)
        print(l1, r1, l2, r2)


if __name__ == "__main__":
    main()
