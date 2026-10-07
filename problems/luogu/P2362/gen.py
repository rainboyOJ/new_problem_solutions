#!/usr/bin/env python3
import random


def main():
    random.seed()
    T = random.randint(1, 3)
    print(T)
    for _ in range(T):
        n = random.randint(1, 12)
        arr = [str(random.randint(1, 20)) for _ in range(n)]
        print(n, *arr)


if __name__ == "__main__":
    main()
