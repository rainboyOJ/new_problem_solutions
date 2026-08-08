#!/usr/bin/env python3
import random


def main():
    random.seed()

    need_volume = random.randint(0, 25)
    n = random.randint(0, 14)
    stamina = random.randint(0, 25)

    print(need_volume, n, stamina)
    for _ in range(n):
        k = random.randint(0, 20)
        m = random.randint(0, 20)
        print(k, m)


if __name__ == "__main__":
    main()
