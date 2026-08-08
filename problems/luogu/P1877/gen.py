#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 12)
    max_level = random.randint(1, 20)
    begin_level = random.randint(0, max_level)
    changes = [random.randint(1, max_level) for _ in range(n)]

    print(n, begin_level, max_level)
    print(*changes)


if __name__ == "__main__":
    main()
