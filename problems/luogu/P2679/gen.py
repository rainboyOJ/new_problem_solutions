#!/usr/bin/env python3
import random


def random_string(length):
    return "".join(random.choice("ab") for _ in range(length))


def main():
    random.seed()
    n = random.randint(1, 10)
    m = random.randint(1, min(6, n))
    k = random.randint(1, m)
    print(n, m, k)
    print(random_string(n))
    print(random_string(m))


if __name__ == "__main__":
    main()
import random


def main():
    random.seed()
    # TODO: generate input for this problem.


if __name__ == "__main__":
    main()
