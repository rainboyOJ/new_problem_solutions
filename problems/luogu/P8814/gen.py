#!/usr/bin/env python3
import random


def main():
    random.seed()

    k = random.randint(1, 40)
    print(k)
    for _ in range(k):
        if random.random() < 0.65:
            p = random.randint(1, 300)
            q = random.randint(p, 300)
            n = p * q
            ed = (p - 1) * (q - 1) + 1
            e = random.randint(1, ed)
            while ed % e != 0:
                e = random.randint(1, ed)
            d = ed // e
        else:
            n = random.randint(1, 90000)
            e = random.randint(1, 500)
            d = random.randint(1, 500)
        print(n, e, d)


if __name__ == "__main__":
    main()
