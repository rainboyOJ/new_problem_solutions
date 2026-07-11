#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 80)
    print(t)
    used = set()
    for _ in range(t):
        while True:
            m = random.randint(1, 30)
            k = random.randint(1, 31)
            if (m, k) not in used:
                used.add((m, k))
                break
        print(m, k)


if __name__ == "__main__":
    main()
