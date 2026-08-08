#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 20)
    print(n)
    heights = random.sample(range(1, 200), n)
    for h in heights:
        v = random.randint(1, 20)
        print(h, v)


if __name__ == "__main__":
    main()
