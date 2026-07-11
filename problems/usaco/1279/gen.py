#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    print(n)
    for _ in range(n):
        row = "".join(random.choice("RD") for _ in range(n))
        c = random.randint(1, 30)
        print(row, c)
    print(" ".join(str(random.randint(1, 30)) for _ in range(n)))

    q = random.randint(1, 20)
    print(q)
    for _ in range(q):
        x = random.randint(1, n)
        y = random.randint(1, n)
        print(x, y)


if __name__ == "__main__":
    main()
