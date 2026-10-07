#!/usr/bin/env python3
import random


def main():
    random.seed()

    p1 = random.randint(1, 3)
    p2 = random.randint(1, 4)
    p3 = random.randint(1, 2)

    alphabet = "abcdefghijklmnopqrstuvwxyz0123456789-"
    length = random.randint(1, 20)
    s = "".join(random.choice(alphabet) for _ in range(length))

    print(p1, p2, p3)
    print(s)


if __name__ == "__main__":
    main()
