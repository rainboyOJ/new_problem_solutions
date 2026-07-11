#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 20)
    print(t)
    for _ in range(t):
        n = random.randint(1, 8)
        k = random.randint(1, 3)
        print(n, k)
        a = [str(random.randint(1, k)) for _ in range(n)]
        print(" ".join(a))


if __name__ == "__main__":
    main()
