#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 80)
    m = random.randint(1, 120)
    print(n, m)
    print(" ".join(str(random.randint(1, 100)) for _ in range(n)))
    for _ in range(m):
        op = random.randint(1, 2)
        l = random.randint(1, n)
        r = random.randint(l, n)
        if op == 1:
            print(op, l, r, random.randint(1, 50))
        else:
            print(op, l, r)


if __name__ == "__main__":
    main()
import random


def main():
    random.seed()
    # TODO: generate input for this problem.


if __name__ == "__main__":
    main()
