#!/usr/bin/env python3
"""生成 P5836 小数据：随机树 + 随机品种与随机查询，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    m = random.randint(1, 60)
    print(n, m)
    # 随机品种串：第 i 个字符是节点 i 的奶牛品种。
    print("".join(random.choice("GH") for _ in range(n)))
    # 随机生成一棵树：第 i 个节点 (i >= 2) 从 1..i-1 中随机选父亲。
    for i in range(2, n + 1):
        fa = random.randint(1, i - 1)
        print(fa, i)
    # 随机查询：两个端点随意，允许 a == b。
    for _ in range(m):
        a = random.randint(1, n)
        b = random.randint(1, n)
        print(a, b, random.choice("GH"))


if __name__ == "__main__":
    main()
