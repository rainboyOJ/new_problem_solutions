#!/usr/bin/env python3
import random


def main():
    random.seed()
    k = random.randint(1, 5)
    n = random.randint(2, 8)

    print(k, n)
    for _ in range(k):
        perm = list(range(1, n + 1))
        random.shuffle(perm)
        print(" ".join(str(x) for x in perm))


if __name__ == "__main__":
    main()
