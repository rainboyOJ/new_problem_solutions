#!/usr/bin/env python3
import random


def main():
    random.seed()
    q = random.randint(1, 20)
    print(q)
    for _ in range(q):
        n = random.randint(1, 8)
        s = "".join(random.choice("MO") for _ in range(n))
        print(s)


if __name__ == "__main__":
    main()
