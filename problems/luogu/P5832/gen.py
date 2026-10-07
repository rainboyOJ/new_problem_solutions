#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 20)
    print(n)
    print("".join(random.choice("ABCDEF") for _ in range(n)))


if __name__ == "__main__":
    main()
