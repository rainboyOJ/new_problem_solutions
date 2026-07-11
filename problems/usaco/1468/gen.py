#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 50)
    print(n)
    a = [str(random.randint(1, n)) for _ in range(n)]
    print(" ".join(a))


if __name__ == "__main__":
    main()
