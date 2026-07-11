#!/usr/bin/env python3
import random
import string


def main():
    random.seed()
    n = random.randint(1, 30)
    alphabet = string.ascii_uppercase[: random.randint(1, 8)]
    s = "".join(random.choice(alphabet) for _ in range(n))

    print(n)
    print(s)


if __name__ == "__main__":
    main()
