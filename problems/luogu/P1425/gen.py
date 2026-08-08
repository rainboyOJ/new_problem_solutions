#!/usr/bin/env python3
import random


def main():
    random.seed()

    start = random.randint(0, 24 * 60 - 1)
    duration = random.randint(1, 24 * 60 - start)
    end = start + duration

    a, b = divmod(start, 60)
    c, d = divmod(end, 60)
    print(a, b, c, d)


if __name__ == "__main__":
    main()
