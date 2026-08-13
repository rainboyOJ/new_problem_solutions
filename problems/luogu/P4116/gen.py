#!/usr/bin/env python3
"""生成 P4116 小数据：随机树 n<=30，m 次黑白切换与根路径第一个黑点查询，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(2, 30)
    m = random.randint(1, 40)
    print(n, m)
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        print(p, i)
    for _ in range(m):
        op = random.randint(0, 1)
        x = random.randint(1, n)
        print(op, x)


if __name__ == "__main__":
    main()
