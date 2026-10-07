#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 6)
    m = random.randint(10, 40)
    q = random.randint(1, 4)
    l = random.randint(1, 3)
    print(n, m, q, l)

    for _ in range(n):
        print(" ".join(str(random.randint(1, 15)) for _ in range(l)))

    print(" ".join(str(random.randint(1, 10)) for _ in range(n)))

    for _ in range(2 * q):
        print(1, random.randint(1, 8))
        if random.randint(0, 1):
            print(2, random.randint(1, 5))


if __name__ == "__main__":
    main()
