#!/usr/bin/env python3
import random
import string


CHARS = string.ascii_lowercase + string.ascii_uppercase + string.digits + "_@"


def main():
    random.seed()
    n = random.randint(1, 40)
    L = random.randint(1, 8)
    pool = set()
    alphabet_len = random.randint(2, min(8, len(CHARS)))
    alphabet = CHARS[:alphabet_len]
    while alphabet_len ** L < n:
        alphabet_len = min(alphabet_len + 1, len(CHARS))
        alphabet = CHARS[:alphabet_len]
    while len(pool) < n:
        pool.add("".join(random.choice(alphabet) for _ in range(L)))
    arr = list(pool)
    print(n, L, 64)
    for s in arr:
        print(s)


if __name__ == "__main__":
    main()
