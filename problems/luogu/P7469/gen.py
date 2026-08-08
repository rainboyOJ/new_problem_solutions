#!/usr/bin/env python3
import random
import string


def rand_str(n: int, alphabet: str) -> str:
    return "".join(random.choice(alphabet) for _ in range(n))


def main():
    random.seed()
    n = random.randint(1, 8)
    alphabet = string.ascii_lowercase[: random.randint(2, 4)]
    s = rand_str(n, alphabet)
    t = rand_str(n, alphabet)
    print(n)
    print(s)
    print(t)


if __name__ == "__main__":
    main()
