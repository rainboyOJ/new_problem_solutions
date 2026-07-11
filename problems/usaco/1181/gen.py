#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 20)
    print(t)
    for _ in range(t):
        n = random.randint(1, 8)
        print(n)
        print(" ".join(str(random.randint(0, 20)) for _ in range(n)))


if __name__ == "__main__":
    main()
