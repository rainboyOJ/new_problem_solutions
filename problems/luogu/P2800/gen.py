#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 18)
    print(n)
    h = [str(random.randint(1, 20)) for _ in range(n)]
    print(" ".join(h))


if __name__ == "__main__":
    main()
