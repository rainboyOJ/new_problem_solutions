#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(3, 9)
    values = sorted(random.randint(0, 40) for _ in range(n))
    print(1)
    print(n)
    print(*values)


if __name__ == "__main__":
    main()
