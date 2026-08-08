#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 12)
    print(n)

    if n > 1:
        parents = [str(random.randint(0, i - 1)) for i in range(1, n)]
        print(" ".join(parents))
    else:
        print()

    q = random.randint(1, 25)
    print(q)
    for _ in range(q):
        op = random.choice(["install", "uninstall"])
        x = random.randint(0, n - 1)
        print(op, x)


if __name__ == "__main__":
    main()
