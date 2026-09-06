#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    print(n)
    print(''.join(random.choice('01') for _ in range(n)))


if __name__ == "__main__":
    main()
