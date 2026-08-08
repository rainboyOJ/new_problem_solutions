#!/usr/bin/env python3
import random
import string


DNA = "AGCT"


def main():
    random.seed()
    n = random.randint(1, 5)
    m = random.randint(1, n)
    k = random.randint(1, 4)
    arr = []
    for _ in range(n):
        length = random.randint(1, 6)
        arr.append("".join(random.choice(DNA) for _ in range(length)))
    print(n, m, k)
    for s in arr:
        print(s)


if __name__ == "__main__":
    main()
