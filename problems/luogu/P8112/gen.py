#!/usr/bin/env python3
import random
import sys


def rand_str(n: int, alpha: str = "ab") -> str:
    return "".join(random.choice(alpha) for _ in range(n))


def main() -> None:
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    m = random.randint(1, 8)
    n = random.randint(1, 30)
    t = rand_str(m)
    s = rand_str(n)

    print(m, n)
    print(t)
    print(s)


if __name__ == "__main__":
    main()
