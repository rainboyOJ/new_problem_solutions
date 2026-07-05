#!/usr/bin/env python3
import random


def main():
    t = random.randint(1, 3)
    print(t)
    for _ in range(t):
        n = random.randint(1, 8)
        m = random.randint(1, 8)
        k = random.randint(1, 80)
        x = random.randint(1, n)
        y = random.randint(1, m)
        d = random.randint(0, 3)
        print(n, m, k)
        print(x, y, d)
        for i in range(1, n + 1):
            row = []
            for j in range(1, m + 1):
                if i == x and j == y:
                    row.append(".")
                else:
                    row.append("x" if random.randint(1, 5) == 1 else ".")
            print("".join(row))


if __name__ == "__main__":
    main()
