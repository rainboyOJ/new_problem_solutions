#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    print(n)
    print(" ".join(str(random.randint(1, 9999)) for _ in range(n)))


if __name__ == "__main__":
    main()
