#!/usr/bin/env python3
import random
import sys


def main() -> None:
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    n = random.randint(1, 10)
    m = random.randint(2, 6)
    cost1 = random.randint(0, 10)
    cost2 = random.randint(0, 10)
    print(n, m, cost1, cost2)
    for _ in range(m):
        row = []
        for _ in range(n):
            if random.randint(0, 99) < 15:
                row.append("-1")
            else:
                row.append(str(random.randint(0, 20)))
        print(" ".join(row))


if __name__ == "__main__":
    main()
