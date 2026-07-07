#!/usr/bin/env python3
import random


def main():
    random.seed()
    special = [1, 2, 3, 4, 7, 8, 15, 16, 31, 32, 137, 1315, 20000]
    if random.randint(1, 4) == 1:
        n = random.choice(special)
    else:
        n = random.randint(1, 20000)
    print(n)


if __name__ == "__main__":
    main()
