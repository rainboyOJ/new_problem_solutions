#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 3)
    print(t)
    for _ in range(t):
        n = random.randint(1, 7)
        a = []
        for x in range(1, n + 1):
            a.append(x)
            a.append(x)
        random.shuffle(a)
        print(n)
        print(*a)


if __name__ == "__main__":
    main()
