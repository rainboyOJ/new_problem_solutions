#!/usr/bin/env python3
import random
import sys


def rand_str(length: int, alphabet: str = "abc") -> str:
    return "".join(random.choice(alphabet) for _ in range(length))


def main() -> None:
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    n = random.randint(1, 40)

    if random.randint(0, 1) == 0:
        base_len = random.randint(1, n)
        base = rand_str(base_len)
        repeat = (n + base_len - 1) // base_len
        s = (base * repeat)[:n]
    else:
        s = rand_str(n)

    print(n)
    print(s)


if __name__ == "__main__":
    main()
