#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.choice([4, 6, 8, 10, 12])
    vals = list(range(1, n * (n - 1) // 2 + 1))
    random.shuffle(vals)

    idx = 0
    print(n)
    for i in range(n - 1):
        row = []
        for j in range(i + 1, n):
            row.append(str(vals[idx]))
            idx += 1
        print(" ".join(row))


if __name__ == "__main__":
    main()
