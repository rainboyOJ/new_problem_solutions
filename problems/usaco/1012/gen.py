#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    chars = ["H", "G"]

    a = []
    b = []
    for _ in range(n):
        a.append(random.choice(chars))
        b.append(random.choice(chars))

    print(n)
    print("".join(a))
    print("".join(b))


if __name__ == "__main__":
    main()
