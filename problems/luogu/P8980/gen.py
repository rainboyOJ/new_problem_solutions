#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 3)
    print(t)
    for _ in range(t):
        n = random.randint(1, 40)
        q = random.randint(1, 8)
        print(n, q)
        arr = [str(random.randint(1, n)) for _ in range(q)]
        print(" ".join(arr))


if __name__ == "__main__":
    main()
