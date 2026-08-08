#!/usr/bin/env python3
import random
import string


def rand_str(n: int, alphabet: str) -> str:
    return "".join(random.choice(alphabet) for _ in range(n))


def main():
    random.seed()
    half = random.randint(1, 8)
    base = rand_str(half, string.ascii_uppercase[: random.randint(2, 4)])
    mode = random.randint(0, 2)

    if mode == 0:
        extra = random.choice(string.ascii_uppercase[:4])
        pos = random.randint(0, half)
        u = base[:pos] + extra + base[pos:] + base
    elif mode == 1:
        extra = random.choice(string.ascii_uppercase[:4])
        pos = random.randint(0, half)
        u = base + base[:pos] + extra + base[pos:]
    else:
        u = rand_str(2 * half + 1, string.ascii_uppercase[: random.randint(2, 4)])

    print(len(u))
    print(u)


if __name__ == "__main__":
    main()
