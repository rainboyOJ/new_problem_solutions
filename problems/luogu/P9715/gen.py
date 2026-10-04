#!/usr/bin/env python3
"""P9715「QFOI R1」头 的随机数据生成器，输出到 stdout。

对拍时由 duipai.py 传入 DUPAI_SEED，同一个种子一定能复现同一份数据；
不传时使用系统随机种子，方便多跑几组不同的数据。

brute.cpp 开的是 100 x 100 的定长网格，按格子模拟每次涂色，
所以这里把 n、m 控制在 100 以内，q 也压到 brute 能跑完的量级。
数据分两类：

1. 覆盖型：小网格 + 随机操作，检查一般情形；
2. 边界型：n=1 或 m=1、整行整列全涂、k 很大但格子很少、只有 t=1、
   只有 op=1 等，专门盯容易写错的边界。
"""

import os
import random

MAX_GRID = 100  # 与 brute.cpp 的网格上限保持一致


def gen_tiny():
    """极小数据：网格和操作都很少，容易手算，对拍最先跑它。"""
    n = random.randint(1, 4)
    m = random.randint(1, 4)
    k = random.randint(1, 3)
    q = random.randint(1, 6)
    return build(n, m, k, q, t_choice=(0, 1), op_choice=(1, 2))


def gen_small():
    n = random.randint(1, 10)
    m = random.randint(1, 10)
    k = random.randint(1, 6)
    q = random.randint(2, 25)
    return build(n, m, k, q, t_choice=(0, 1), op_choice=(1, 2))


def gen_mid():
    n = random.randint(5, 40)
    m = random.randint(5, 40)
    k = random.randint(2, 20)
    q = random.randint(20, 160)
    return build(n, m, k, q, t_choice=(0, 1), op_choice=(1, 2))


def gen_wide():
    """大网格、少操作：让“整行 / 整列”的规模差距更明显。"""
    n = random.randint(60, MAX_GRID)
    m = random.randint(60, MAX_GRID)
    k = random.randint(1, 10)
    q = random.randint(10, 70)
    return build(n, m, k, q, t_choice=(0, 1), op_choice=(1, 2))


def gen_thin_row():
    """只有一行：所有操作都退化成对同一行的区间覆盖，边界最容易出错。"""
    n = 1
    m = random.randint(1, MAX_GRID)
    k = random.randint(1, 8)
    q = random.randint(1, 60)
    return build(n, m, k, q, t_choice=(0, 1), op_choice=(1, 2))


def gen_thin_col():
    """只有一列。"""
    n = random.randint(1, MAX_GRID)
    m = 1
    k = random.randint(1, 8)
    q = random.randint(1, 60)
    return build(n, m, k, q, t_choice=(0, 1), op_choice=(1, 2))


def gen_only_overwrite():
    """子任务：所有操作都是 t=1（只覆盖）。此时没有“第一次涂色”的分支。"""
    n = random.randint(1, 30)
    m = random.randint(1, 30)
    k = random.randint(1, 10)
    q = random.randint(1, 120)
    return build(n, m, k, q, t_choice=(1,), op_choice=(1, 2))


def gen_only_skip():
    """全部是 t=0（不覆盖已染色格子）。答案只由每个格子的第一次涂色决定。"""
    n = random.randint(1, 30)
    m = random.randint(1, 30)
    k = random.randint(1, 10)
    q = random.randint(1, 120)
    return build(n, m, k, q, t_choice=(0,), op_choice=(1, 2))


def gen_only_row():
    """子任务：只有 op=1。此时每种颜色的格子数一定是 m 的倍数。"""
    n = random.randint(1, 60)
    m = random.randint(1, 60)
    k = random.randint(1, 10)
    q = random.randint(1, 120)
    return build(n, m, k, q, t_choice=(0, 1), op_choice=(1,))


def gen_full_range():
    """每次都涂满整行或整列：区间端点全部落在边界上，反复互相覆盖。"""
    n = random.randint(1, 20)
    m = random.randint(1, 20)
    k = random.randint(1, 5)
    q = random.randint(2, 80)
    ops = []
    for _ in range(q):
        op = random.randint(1, 2)
        t = random.randint(0, 1)
        c = random.randint(1, k)
        if op == 1:
            ops.append((op, 1, n, c, t))
        else:
            ops.append((op, 1, m, c, t))
    return n, m, k, ops


def gen_many_colors():
    """颜色数远大于格子数：绝大多数颜色的答案必须是 0。"""
    n = random.randint(1, 6)
    m = random.randint(1, 6)
    k = random.randint(500, 2000)
    q = random.randint(1, 40)
    return build(n, m, k, q, t_choice=(0, 1), op_choice=(1, 2))


def build(n, m, k, q, t_choice, op_choice):
    """随机生成 q 个操作；t 从 t_choice 里取，op 从 op_choice 里取。"""
    ops = []
    for _ in range(q):
        op = random.choice(op_choice)
        t = random.choice(t_choice)
        c = random.randint(1, k)
        if op == 1:
            l = random.randint(1, n)
            r = random.randint(l, n)
        else:
            l = random.randint(1, m)
            r = random.randint(l, m)
        ops.append((op, l, r, c, t))
    return n, m, k, ops


def main():
    seed_text = os.environ.get("DUPAI_SEED")
    random.seed(None if seed_text is None else int(seed_text))

    generators = [
        gen_tiny,
        gen_tiny,
        gen_small,
        gen_small,
        gen_mid,
        gen_mid,
        gen_wide,
        gen_thin_row,
        gen_thin_col,
        gen_only_overwrite,
        gen_only_skip,
        gen_only_row,
        gen_full_range,
        gen_many_colors,
    ]
    n, m, k, ops = random.choice(generators)()

    out = ["%d %d %d %d" % (n, m, k, len(ops))]
    for op, l, r, c, t in ops:
        out.append("%d %d %d %d %d" % (op, l, r, c, t))
    print("\n".join(out))


if __name__ == "__main__":
    main()
