#!/usr/bin/env python3
import random


def main():
    random.seed()

    q = random.randint(1, 20)
    print(q)
    for _ in range(q):
        print(random.randint(0, 200000))


if __name__ == "__main__":
    main()
