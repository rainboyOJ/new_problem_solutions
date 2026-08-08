#!/usr/bin/env python3
import random


def main():
    t = random.randint(1, 20)
    print(t)
    for _ in range(t):
        print(random.randint(1, 200))


if __name__ == "__main__":
    main()
