#!/usr/bin/env python3
import random


def main():
    n = random.randint(2, 20)
    if n % 2 == 1:
        n += 1
    print("".join(random.choice("()") for _ in range(n)))


if __name__ == "__main__":
    main()
