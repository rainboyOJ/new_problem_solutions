#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 20)
    q = random.randint(1, 40)
    a = [random.randint(1, 10) for _ in range(n)]

    print(n, q)
    print(*a)

    modify_cnt = 0
    for _ in range(q):
        if modify_cnt < 10 and random.randint(1, 100) <= 35:
            x = random.randint(1, n)
            v = random.randint(1, 10)
            print(1, x, v)
            modify_cnt += 1
        else:
            x = random.randint(1, n)
            print(2, x)


if __name__ == "__main__":
    main()
