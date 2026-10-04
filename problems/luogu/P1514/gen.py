#!/usr/bin/env python3
"""P1514 引水入城的随机数据生成器，输出到 stdout。

对拍时由 duipai.py 传入 DUPAI_SEED，同一个种子一定能复现同一份数据；
不传时使用系统随机种子，方便多跑几组不同的数据。

由于暴力解要枚举第一行所有 2^m 种建站方案，这里的 m 最大只到 14，
否则 brute 会超时。n 可以放大到 60，用来覆盖“干旱区通不了水”的情形。
"""

import os
import random


def gen_tiny():
    """极小数据：海拔取值很少，容易出现无解和重复海拔。"""
    n = random.randint(1, 4)
    m = random.randint(1, 4)
    return build_plain(n, m, random.randint(1, 3))


def gen_small():
    n = random.randint(2, 6)
    m = random.randint(2, 6)
    return build_plain(n, m, random.randint(1, 4))


def gen_mid():
    n = random.randint(2, 9)
    m = random.randint(2, 9)
    return build_plain(n, m, random.randint(1, 6))


def gen_tall():
    """高瘦网格：行多列少，容易整体无解。n 接近暴力数组上限。"""
    n = random.randint(2, 60)
    m = random.randint(2, 5)
    return build_plain(n, m, random.randint(1, 5))


def gen_flat():
    """扁网格：列多行少，测试 m 接近暴力上限时的情况。"""
    n = random.randint(1, 4)
    m = random.randint(8, 14)
    return build_plain(n, m, random.randint(1, 4))


def gen_feasible_blocks():
    """一定可行的构造：每列自上到下严格递减，所以每列底部都能被自己那列的
    蓄水厂灌到，整体一定可行。

    再让海拔沿着“离分块中心越远越低”变化，水会往分块中心汇聚，
    于是每个蓄水厂覆盖的区间往往是某个分块的一部分，区间之间差异明显，
    能真正考验区间覆盖贪心（答案通常大于 1）。
    """
    n = random.randint(2, 14)
    m = random.randint(4, 14)
    block = random.randint(2, 4)      # 每个分块的宽度
    offset = random.randint(0, block - 1)

    grid = []
    for i in range(n):
        row = []
        for j in range(m):
            # 离所在分块中心的距离
            local = (j + offset) % block
            dist = abs(local - (block - 1) / 2.0)
            # 行号越大海拔越低（每行降 1000），离中心越远海拔越低（每列降 10）
            value = (n - i) * 1000 - int(dist * 10) + random.randint(0, 9)
            row.append(value)
        grid.append(row)
    return n, m, grid


def build_plain(n, m, top):
    """在 [1, top] 内随机取海拔，可能可行也可能不可行。"""
    grid = []
    for _ in range(n):
        row = [random.randint(1, top) for _ in range(m)]
        grid.append(row)
    return n, m, grid


def main():
    seed_text = os.environ.get("DUPAI_SEED")
    random.seed(None if seed_text is None else int(seed_text))

    generators = [
        gen_tiny,
        gen_tiny,
        gen_small,
        gen_small,
        gen_mid,
        gen_tall,
        gen_flat,
        gen_feasible_blocks,
        gen_feasible_blocks,
    ]
    n, m, grid = random.choice(generators)()

    print(n, m)
    for row in grid:
        print(" ".join(str(value) for value in row))


if __name__ == "__main__":
    main()
