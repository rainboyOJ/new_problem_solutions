#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(3, 30)
    print(n)
    print("".join(random.choice("GH") for _ in range(n)))


if __name__ == "__main__":
    main()
