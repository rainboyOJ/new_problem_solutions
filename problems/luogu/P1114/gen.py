#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 60)
    print(n)
    print(" ".join(str(random.randint(0, 1)) for _ in range(n)))


if __name__ == "__main__":
    main()
