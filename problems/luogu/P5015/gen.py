#!/usr/bin/env python3
import random


def main():
    random.seed()
    chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 "
    n = random.randint(1, 20)
    s = "".join(random.choice(chars) for _ in range(n))
    print(s)


if __name__ == "__main__":
    main()
