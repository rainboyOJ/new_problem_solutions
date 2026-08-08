#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 120)
    m = random.randint(1, 120)
    print(n)
    print(" ".join(str(random.randint(1, 50)) for _ in range(n)))
    print(m)
    for _ in range(m):
        l = random.randint(1, n)
        r = random.randint(l, n)
        print(l, r)


if __name__ == "__main__":
    main()
import random


def main():
    random.seed()
    # TODO: generate input for this problem.


if __name__ == "__main__":
    main()
