#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 80)
    l = random.randint(1, n)
    r = random.randint(l, n)
    print(n, l, r)
    values = [0]
    for _ in range(n):
        values.append(random.randint(-20, 50))
    print(" ".join(str(x) for x in values))


if __name__ == "__main__":
    main()
import random


def main():
    random.seed()
    # TODO: generate input for this problem.


if __name__ == "__main__":
    main()
