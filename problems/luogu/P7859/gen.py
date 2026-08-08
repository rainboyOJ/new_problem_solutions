#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 20)
    pairs = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            pairs.append((i, j))
    random.shuffle(pairs)
    m = random.randint(0, min(len(pairs), 30))
    print(n, m)
    for i in range(m):
        print(pairs[i][0], pairs[i][1])


if __name__ == "__main__":
    main()
