#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 12)
    k = random.randint(0, n)
    print(n, k)
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        print(i, p)

    nodes = list(range(1, n + 1))
    random.shuffle(nodes)
    for i in range(k):
        print(nodes[i], random.randint(1, 3))


if __name__ == "__main__":
    main()
