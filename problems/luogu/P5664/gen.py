#!/usr/bin/env python3
import random


def rand_cell() -> int:
    if random.randint(0, 9) < 4:
        return 0
    return random.randint(1, 5)


def main():
    random.seed()

    n = random.randint(1, 7)
    m = random.randint(1, 5)

    print(n, m)
    for _ in range(n):
        row = [rand_cell() for _ in range(m)]
        print(*row)


if __name__ == "__main__":
    main()
