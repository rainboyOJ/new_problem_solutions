#!/usr/bin/env python3
"""生成 P3178 小数据：随机树 n<=30，m 次随机操作，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    m = random.randint(1, 100)
    print(n, m)
    print(*[random.randint(-1000, 1000) for _ in range(n)])
    # 随机树：每个点 i (2..n) 随机选一个父亲，保证以 1 为根连通。
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        print(parent, i)
    for _ in range(m):
        opt = random.randint(1, 3)
        x = random.randint(1, n)
        if opt == 3:
            print(3, x)
        else:
            a = random.randint(-1000, 1000)
            print(opt, x, a)


if __name__ == "__main__":
    main()
