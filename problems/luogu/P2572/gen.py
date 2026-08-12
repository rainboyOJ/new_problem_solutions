#!/usr/bin/env python3
"""生成 P2572 小数据：n 个 01 数，m 次操作（赋值 0/1、翻转、两种查询），规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    m = random.randint(1, 100)
    print(n, m)
    # 初始 01 序列
    for _ in range(n):
        print(random.randint(0, 1), end=" ")
    print()
    for _ in range(m):
        op = random.randint(0, 4)
        l = random.randint(0, n - 1)
        r = random.randint(0, n - 1)
        if l > r:
            l, r = r, l
        print(op, l, r)


if __name__ == "__main__":
    main()
