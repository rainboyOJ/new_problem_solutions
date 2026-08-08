#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(2, 10)
    print(n)
    arr = [str(random.randint(1, 10)) for _ in range(n)]
    print(" ".join(arr))

    q = random.randint(1, 5)
    print(q)
    for _ in range(q):
        print(random.randint(1, n))


if __name__ == "__main__":
    main()
