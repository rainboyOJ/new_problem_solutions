#!/usr/bin/env python3

import random


def main():
    n = random.randint(1, 6)
    t = random.randint(1, 60)
    vals = random.sample(range(1, 21), n)
    cnts = [random.randint(0, 6) for _ in range(n)]

    print(n, t)
    print(*vals)
    print(*cnts)


if __name__ == "__main__":
    main()
