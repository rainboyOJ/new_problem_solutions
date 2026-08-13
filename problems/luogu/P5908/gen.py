#!/usr/bin/env python3
"""生成 P5908 小数据：随机树，规模适合暴力对拍。

每个节点 i（2..n）的父节点在 1..i-1 里随机取，天然是一棵以 1 为根的树。
"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    d = random.randint(0, n - 1)
    print(n, d)
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        print(p, i)


if __name__ == "__main__":
    main()
