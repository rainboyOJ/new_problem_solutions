#!/usr/bin/env python3
"""生成 P3398 小数据：随机树 n <= 30，m 次随机路径查询，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    m = random.randint(1, 20)
    print(n, m)
    # 第 i 个点随机连到 [1, i-1] 中的任意一个点，保证是一棵以 1 为根的随机树。
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        print(parent, i)
    # m 次随机查询，端点允许重合（a == b 表示路径退化成单点）。
    for _ in range(m):
        a = random.randint(1, n)
        b = random.randint(1, n)
        c = random.randint(1, n)
        d = random.randint(1, n)
        print(a, b, c, d)


if __name__ == "__main__":
    main()
