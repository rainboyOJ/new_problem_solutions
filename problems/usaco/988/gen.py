#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 8)
    perm = list(range(1, n + 1))
    random.shuffle(perm)

    b = []
    for i in range(n - 1):
        b.append(perm[i] + perm[i + 1])

    print(n)
    print(" ".join(str(x) for x in b))


if __name__ == "__main__":
    main()
