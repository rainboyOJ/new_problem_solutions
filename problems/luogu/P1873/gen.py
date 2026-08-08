#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 50)
    h = [random.randint(1, 200) for _ in range(n)]
    total = sum(h)
    need = random.randint(1, max(1, total - 1))

    print(n, need)
    print(" ".join(map(str, h)))


if __name__ == "__main__":
    main()
