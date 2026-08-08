#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 16)
    print(n)
    print(" ".join(str(random.randint(-20, 30)) for _ in range(n)))
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        print(parent, i)


if __name__ == "__main__":
    main()
