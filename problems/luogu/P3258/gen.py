#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 120)
    route = [random.randint(1, n) for _ in range(n)]

    print(n)
    print(" ".join(str(x) for x in route))
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        print(parent, i)


if __name__ == "__main__":
    main()
