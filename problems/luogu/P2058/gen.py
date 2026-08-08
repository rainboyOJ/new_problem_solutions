#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 80)
    now = 0
    print(n)
    for _ in range(n):
        now += random.randint(0, 50000)
        k = random.randint(1, 8)
        countries = [str(random.randint(1, 20)) for _ in range(k)]
        print(now, k, *countries)


if __name__ == "__main__":
    main()
