#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 20)
    print(n)
    arr = [str(random.randint(0, 8)) for _ in range(n)]
    print(" ".join(arr))


if __name__ == "__main__":
    main()
