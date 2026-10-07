#!/usr/bin/env python3
import random
import sys


def rand_str(length: int, alphabet: str = "abcd") -> str:
    return "".join(random.choice(alphabet) for _ in range(length))


def main() -> None:
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    s = rand_str(random.randint(8, 30))
    q = random.randint(1, 8)
    print(s)
    print(q)
    for _ in range(q):
        print(rand_str(8))


if __name__ == "__main__":
    main()
