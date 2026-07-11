#!/usr/bin/env python3
import random


def main():
    random.seed()
    tests = random.randint(1, 6)
    print(tests)
    print()
    for _ in range(tests):
        n = random.randint(1, 8)
        k = random.randint(1, n)
        print(n)
        for _ in range(n):
            print("".join(random.choice("*.") for _ in range(n)))
        print(k)
        for _ in range(k):
            print("".join(random.choice("*.") for _ in range(k)))
        print()


if __name__ == "__main__":
    main()
