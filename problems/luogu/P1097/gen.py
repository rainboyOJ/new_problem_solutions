#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 50)
    kinds = [random.randint(0, 200) for _ in range(random.randint(1, 8))]
    print(n)
    for _ in range(n):
        print(random.choice(kinds))


if __name__ == "__main__":
    main()
