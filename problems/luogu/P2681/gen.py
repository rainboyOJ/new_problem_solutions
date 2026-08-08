#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    m = random.randint(1, 30)
    print(n, m)
    print(" ".join(str(random.randint(1, 20)) for _ in range(n)))
    for _ in range(m):
        flag = random.randint(0, 1)
        if flag == 0:
            l = random.randint(1, n)
            r = random.randint(l, n)
            print(flag, l, r)
        else:
            x = random.randint(1, n)
            y = random.randint(1, 20)
            print(flag, x, y)


if __name__ == "__main__":
    main()
