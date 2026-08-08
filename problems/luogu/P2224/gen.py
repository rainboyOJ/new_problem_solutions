#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 10)
    print(n)
    for _ in range(n):
        vals = [random.randint(0, 5) for _ in range(3)]
        if vals == [0, 0, 0]:
            vals[random.randint(0, 2)] = random.randint(1, 5)
        print(*vals)


if __name__ == "__main__":
    main()
