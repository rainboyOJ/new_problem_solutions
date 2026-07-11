#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 35)
    alphabet = "bessiexyz"
    print("".join(random.choice(alphabet) for _ in range(n)))


if __name__ == "__main__":
    main()
