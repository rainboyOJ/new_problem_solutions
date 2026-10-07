#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 3)
    m = random.randint(2, 3)
    t = random.randint(1, 3)
    print(n, m, t)

    for _ in range(n - 1):
        print(*[random.randint(0, 9) for _ in range(m)])
    for _ in range(n):
        print(*[random.randint(0, 9) for _ in range(m - 1)])

    boundary_count = 2 * (n + m)
    for _ in range(t):
        k = random.randint(1, min(5, boundary_count))
        positions = random.sample(range(1, boundary_count + 1), k)
        print(k)
        for p in positions:
            x = random.randint(0, 12)
            color = random.randint(0, 1)
            print(x, p, color)


if __name__ == "__main__":
    main()
