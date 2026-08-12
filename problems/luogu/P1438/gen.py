#!/usr/bin/env python3
"""生成 P1438 小数据：n 个数的数列，等差数列区间加 + 单点查询，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    m = random.randint(1, 50)
    print(n, m)
    print(*[random.randint(-200, 200) for _ in range(n)])
    for _ in range(m):
        if random.randint(0, 1) == 0:
            l = random.randint(1, n)
            r = random.randint(l, n)
            K = random.randint(-200, 200)
            D = random.randint(-200, 200)
            print(1, l, r, K, D)
        else:
            p = random.randint(1, n)
            print(2, p)


if __name__ == "__main__":
    main()
