#!/usr/bin/env python3
import random


def main():
    m = random.randint(1, 8)
    n = random.randint(1, 30)
    words = [str(random.randint(1, 15)) for _ in range(n)]
    print(m, n)
    print(" ".join(words))


if __name__ == "__main__":
    main()
