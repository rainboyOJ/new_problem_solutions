#!/usr/bin/env python3
import random


def main():
    random.seed()

    t = random.randint(1, 5)
    print(t)

    for _ in range(t):
        n = random.randint(1, 8)
        print(n)
        w = [str(random.randint(1, 30)) for _ in range(n)]
        e = [str(random.randint(1, 15)) for _ in range(n)]
        print(" ".join(w))
        print(" ".join(e))


if __name__ == "__main__":
    main()
