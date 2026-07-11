#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 20)
    print(t)
    for _ in range(t):
        n = random.choice([2, 4, 6, 8, 10])
        print(n)
        print(" ".join(str(random.randint(1, 20)) for _ in range(n)))


if __name__ == "__main__":
    main()
