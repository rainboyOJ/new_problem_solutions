#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 24)
    alphabet = "abc"
    s = "".join(random.choice(alphabet) for _ in range(n))
    print(n)
    print(s)


if __name__ == "__main__":
    main()
