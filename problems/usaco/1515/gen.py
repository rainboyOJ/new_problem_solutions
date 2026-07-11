#!/usr/bin/env python3
import random
import sys


def main():
    random.seed()
    max_n = 8
    max_m = 20
    if len(sys.argv) >= 2:
        max_n = int(sys.argv[1])
    if len(sys.argv) >= 3:
        max_m = int(sys.argv[2])

    n = random.randint(1, max_n)
    m = random.randint(1, max_m)
    print(n, m)

    for i in range(1, n + 1):
        row = []
        for j in range(1, i + 1):
            if i == j:
                row.append("D")
            else:
                row.append(random.choice(["W", "L", "D"]))
        print("".join(row))

    for _ in range(m):
        s1 = random.randint(1, n)
        s2 = random.randint(1, n)
        print(s1, s2)


if __name__ == "__main__":
    main()
