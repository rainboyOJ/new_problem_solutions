#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 8)
    q = random.randint(1, 12)

    pos = []
    cur = 0
    for _ in range(n):
        cur += random.randint(1, 5)
        pos.append(cur)

    color = [random.randint(0, 1) for _ in range(n)]

    print(n, q)
    print(*pos)
    print(*color)

    alive = []
    for i in range(1, q + 1):
        if not alive or random.randint(0, 1) == 0:
            l = random.randint(1, pos[-1])
            r = random.randint(l, pos[-1] + 2)
            print(1, l, r)
            alive.append(i)
        else:
            x = random.choice(alive)
            print(2, x)
            alive.remove(x)


if __name__ == "__main__":
    main()
