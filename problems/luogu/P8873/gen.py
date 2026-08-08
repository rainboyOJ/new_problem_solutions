#!/usr/bin/env python3
import random


def main():
    random.seed()
    q = random.randint(1, 30)
    print(q)
    for _ in range(q):
        print(random.randint(1, 200000))


if __name__ == "__main__":
    main()
