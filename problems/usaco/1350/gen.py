#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    m = random.randint(1, 10)
    k = random.randint(1, 8)
    weights = random.sample(range(1, 35), n)

    print(n, m, k)
    for w in weights:
        a = random.randint(1, 7)
        print(w, a)


if __name__ == "__main__":
    main()
