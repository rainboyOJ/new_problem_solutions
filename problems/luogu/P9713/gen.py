#!/usr/bin/env python3
"""洛谷 P9713「QFOI R1」抱抱 的随机数据生成器。

输出到 stdout，格式与题目一致：第一行 a b c m，之后 m 行 op k。

可复现：设置环境变量 DUPAI_SEED=<整数> 或传第一个命令行参数 <seed> 可固定随机种子；
都不给时随手取一个种子并写到 stderr，便于回放。

因为 brute.cpp 要真的开 a*b*c 个格子并逐次操作，生成器把体积控制在
MAX_VOLUME 以内、m 控制在 MAX_M 以内，保证暴力能在对拍时限内跑完。
覆盖的数据形态（由 seed 决定，尽量分散）：

  0. 极小数据（a,b,c <= 3, m <= 4），方便直接肉眼核对题意
  1. 小数据（a,b,c <= 100），对应测试点 1~5
  2. b = c = 1 且只有 op=1，对应测试点 6~10
  3. c = 1 且 op 只在 {1,2} 之间，对应测试点 11~15
  4. 某一维退化成 1 的细长蛋糕
  5. 一般数据（a,b,c 都大于 1），并混入大量“无效刀”
  6. 边界数据：k 恒等于整条边长（一次切光）或恒等于 1（几乎不切）
"""

import os
import random
import sys

MAX_VOLUME = 200000  # a*b*c 上限，保证暴力可跑
MAX_M = 200


def rand_abc(rng, lo, hi):
    """随机取三个边长，并保证体积不超过 MAX_VOLUME。"""
    while True:
        a = rng.randint(lo, hi)
        b = rng.randint(lo, hi)
        c = rng.randint(lo, hi)
        if a * b * c <= MAX_VOLUME:
            return a, b, c


def emit_ops(rng, a, b, c, m, ops, shuffle=True):
    """生成 m 次操作；ops 是允许出现的操作种类，k 按对应边长取。"""
    lines = []
    for _ in range(m):
        op = rng.choice(ops)
        limit = {1: a, 2: b, 3: c}[op]
        k = rng.randint(1, limit)
        lines.append("%d %d" % (op, k))
    if shuffle:
        rng.shuffle(lines)
    return lines


def case_tiny(rng, out):
    a, b, c = rand_abc(rng, 1, 3)
    m = rng.randint(1, 4)
    out.append("%d %d %d %d" % (a, b, c, m))
    out.extend(emit_ops(rng, a, b, c, m, [1, 2, 3]))


def case_small(rng, out):
    a, b, c = rand_abc(rng, 1, 100)
    m = rng.randint(1, MAX_M)
    out.append("%d %d %d %d" % (a, b, c, m))
    out.extend(emit_ops(rng, a, b, c, m, [1, 2, 3]))


def case_one_dim_op1(rng, out):
    """对应测试点 6~10：b = c = 1，只出现 op=1。"""
    a = rng.randint(1, 1000)
    m = rng.randint(1, MAX_M)
    out.append("%d 1 1 %d" % (a, m))
    for _ in range(m):
        out.append("1 %d" % rng.randint(1, a))


def case_c_eq_1(rng, out):
    a, b = rng.randint(1, 400), rng.randint(1, 400)
    if a * b > MAX_VOLUME:
        a = b = 300
    m = rng.randint(1, MAX_M)
    out.append("%d %d 1 %d" % (a, b, m))
    out.extend(emit_ops(rng, a, b, 1, m, [1, 2]))


def case_thin(rng, out):
    """某一维退化成 1，另两维一大一小。"""
    which = rng.randint(1, 3)
    dims = [rng.randint(1, 500), rng.randint(1, 500), rng.randint(1, 500)]
    dims[which - 1] = 1
    while dims[0] * dims[1] * dims[2] > MAX_VOLUME:
        i = rng.randint(0, 2)
        dims[i] = max(1, dims[i] // 2)
    a, b, c = dims
    m = rng.randint(1, MAX_M)
    out.append("%d %d %d %d" % (a, b, c, m))
    out.extend(emit_ops(rng, a, b, c, m, [1, 2, 3]))


def case_general(rng, out):
    """一般数据：三维都大于 1，并用“先切大刀再切小刀”制造无效操作。"""
    a, b, c = rand_abc(rng, 2, 200)
    m = rng.randint(1, MAX_M)
    out.append("%d %d %d %d" % (a, b, c, m))
    lines = []
    for _ in range(m // 2):
        op = rng.randint(1, 3)
        limit = {1: a, 2: b, 3: c}[op]
        # 前半段故意用大 k，后半段再补小 k，专门覆盖“这一刀没切到任何方块”的情况
        k = rng.randint(max(1, limit // 2), limit)
        lines.append("%d %d" % (op, k))
    for _ in range(m - m // 2):
        op = rng.randint(1, 3)
        limit = {1: a, 2: b, 3: c}[op]
        k = rng.randint(1, max(1, limit // 2))
        lines.append("%d %d" % (op, k))
    rng.shuffle(lines)
    out.extend(lines)


def case_extreme_k(rng, out):
    a, b, c = rand_abc(rng, 1, 150)
    m = rng.randint(1, MAX_M)
    big = rng.randint(0, 1) == 0
    out.append("%d %d %d %d" % (a, b, c, m))
    for _ in range(m):
        op = rng.randint(1, 3)
        limit = {1: a, 2: b, 3: c}[op]
        k = limit if big else 1
        out.append("%d %d" % (op, k))


CASES = [
    case_tiny,
    case_small,
    case_one_dim_op1,
    case_c_eq_1,
    case_thin,
    case_general,
    case_extreme_k,
]


def main():
    if len(sys.argv) > 1:
        seed = int(sys.argv[1])
    elif "DUPAI_SEED" in os.environ:
        seed = int(os.environ["DUPAI_SEED"])
    else:
        seed = random.randrange(1, 10 ** 9)
        sys.stderr.write("# seed=%d\n" % seed)

    rng = random.Random(seed)
    out = []
    CASES[seed % len(CASES)](rng, out)
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
