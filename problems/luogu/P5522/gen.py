#!/usr/bin/env python3
"""生成 P5522 小数据：n <= 6、m <= 30、q <= 100，规模适合暴力 2^n 枚举对拍。"""
import random

random.seed()


def main():
    n = random.randint(1, 6)
    m = random.randint(1, 30)
    q = random.randint(1, 100)
    print(n, m, q)
    for _ in range(m):
        print("".join(random.choice("01?") for _ in range(n)))
    for _ in range(q):
        if random.random() < 0.5:
            l = random.randint(1, m)
            r = random.randint(l, m)
            print(0, l, r)
        else:
            pos = random.randint(1, m)
            print(1, pos, "".join(random.choice("01?") for _ in range(n)))


if __name__ == "__main__":
    main()
