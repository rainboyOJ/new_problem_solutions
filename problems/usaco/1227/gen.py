#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.choice([2, 4, 6, 8, 10])
    s = []
    for _ in range(n):
        s.append(random.choice(["G", "H"]))
    print(n)
    print("".join(s))


if __name__ == "__main__":
    main()
