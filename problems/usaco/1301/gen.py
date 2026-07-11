#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    k = random.randint(1, 50)
    days = sorted(random.sample(range(1, 300), n))
    print(n, k)
    print(*days)


if __name__ == "__main__":
    main()
