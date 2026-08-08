#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 80)
    print(n)
    arr = [str(random.randint(0, 1)) for _ in range(n)]
    print(" ".join(arr))


if __name__ == "__main__":
    main()
