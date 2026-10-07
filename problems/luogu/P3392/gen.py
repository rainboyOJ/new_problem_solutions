#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(3, 12)
    m = random.randint(1, 12)
    print(n, m)
    colors = "WBR"
    for _ in range(n):
        print("".join(random.choice(colors) for _ in range(m)))


if __name__ == "__main__":
    main()
