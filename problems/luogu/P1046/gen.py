#!/usr/bin/env python3
import random


def main():
    random.seed()
    print(*[random.randint(1, 250) for _ in range(10)])
    print(random.randint(1, 220))


if __name__ == "__main__":
    main()
