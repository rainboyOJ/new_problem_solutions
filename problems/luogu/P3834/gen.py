#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 100)
    m = random.randint(1, 120)
    print(n, m)
    print(" ".join(str(random.randint(0, 1000)) for _ in range(n)))
    for _ in range(m):
        l = random.randint(1, n)
        r = random.randint(l, n)
        k = random.randint(1, r - l + 1)
        print(l, r, k)


if __name__ == "__main__":
    main()
import random


def main():
    random.seed()
    # TODO: generate input for this problem.


if __name__ == "__main__":
    main()
