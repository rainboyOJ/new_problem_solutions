#!/usr/bin/env python3
"""P9247 [集训队互测 2018] 完美的队列 的随机数据生成器，输出到 stdout。

对拍时由 duipai.py / verify.sh 调用。设置环境变量 DUPAI_SEED 即可复现同一份数据
（同一个种子一定得到同一份数据）；不设置时使用系统随机种子，方便多跑几组不同数据。

数据规模刻意压得很小：暴力解 brute.cpp 每次操作都要遍历区间内所有队列并统计
不同权值，所以 n、m、a_i 都只取到十几，既能覆盖边界又不会让 brute 超时。
覆盖的情形：
  - 极小的 n = 1 / m = 1；
  - a_i = 1、a_i = 2、a_i = 10（题面特别提到的特殊测试点性质）；
  - 区间很长（几乎覆盖全部队列）与区间很短（单点）的混合；
  - x 取值很少（大量重复权值）与 x 取值很多（几乎全不同）两种极端。
"""

import os
import random

# 小规模上限：保证 brute.cpp 在几毫秒内跑完
MAX_N = 16
MAX_M = 16


def gen_single_queue():
    """n = 1：所有操作都落在同一个队列上，最纯粹的容量 / 弹出关系。"""
    n = 1
    m = random.randint(1, MAX_M)
    a = [random.choice([1, 1, 2, 3, 5, 10])]
    ops = [(1, 1, random.randint(1, 3)) for _ in range(m)]
    return n, a, ops


def gen_single_op():
    """m = 1：只有一次操作，答案必然是 1。"""
    n = random.randint(1, MAX_N)
    a = [random.randint(1, 10) for _ in range(n)]
    l = random.randint(1, n)
    r = random.randint(l, n)
    ops = [(l, r, random.randint(1, 3))]
    return n, a, ops


def gen_uniform_a(aval):
    """所有队列容量都等于 aval，用来针对 a_i = 1 / 2 / 10 的特殊测试点。"""
    n = random.randint(1, MAX_N)
    m = random.randint(1, MAX_M)
    a = [aval] * n
    ops = []
    for _ in range(m):
        l = random.randint(1, n)
        r = random.randint(l, n)
        ops.append((l, r, random.randint(1, 3)))
    return n, a, ops


def gen_random():
    """一般随机数据：容量、区间、权值都随机。"""
    n = random.randint(1, MAX_N)
    m = random.randint(1, MAX_M)
    a = [random.randint(1, 12) for _ in range(n)]
    xmax = random.choice([1, 2, 3, m])
    ops = []
    for _ in range(m):
        l = random.randint(1, n)
        r = random.randint(l, n)
        ops.append((l, r, random.randint(1, xmax)))
    return n, a, ops


def gen_long_ranges():
    """区间普遍很长：块被整块操作频繁覆盖，考验整块影响的处理。"""
    n = random.randint(2, MAX_N)
    m = random.randint(1, MAX_M)
    a = [random.randint(1, 4) for _ in range(n)]
    ops = []
    for _ in range(m):
        l = random.randint(1, max(1, n // 4))
        r = random.randint(min(n, n - n // 4 + 1), n)
        if r < l:
            l, r = r, l
        ops.append((l, r, random.randint(1, 3)))
    return n, a, ops


def gen_tiny_ranges():
    """区间普遍很短：大量散块操作，考验散块双指针与整块前缀和。"""
    n = random.randint(2, MAX_N)
    m = random.randint(1, MAX_M)
    a = [random.randint(1, 6) for _ in range(n)]
    ops = []
    for _ in range(m):
        l = random.randint(1, n)
        r = min(n, l + random.randint(0, 1))
        ops.append((l, r, random.randint(1, 3)))
    return n, a, ops


def gen_large_capacity():
    """容量很大：大多数操作都不会触发弹出，x 的存活区间一直延伸到结尾。"""
    n = random.randint(1, MAX_N)
    m = random.randint(1, MAX_M)
    a = [random.randint(8, 20) for _ in range(n)]
    ops = []
    for _ in range(m):
        l = random.randint(1, n)
        r = random.randint(l, n)
        ops.append((l, r, random.randint(1, m)))
    return n, a, ops


GENERATORS = [
    gen_single_queue,
    gen_single_queue,
    gen_single_op,
    gen_single_op,
    lambda: gen_uniform_a(1),
    lambda: gen_uniform_a(1),
    lambda: gen_uniform_a(2),
    lambda: gen_uniform_a(2),
    lambda: gen_uniform_a(10),
    gen_random,
    gen_random,
    gen_random,
    gen_long_ranges,
    gen_long_ranges,
    gen_tiny_ranges,
    gen_tiny_ranges,
    gen_large_capacity,
    gen_large_capacity,
]


def main():
    seed_text = os.environ.get("DUPAI_SEED")
    random.seed(None if seed_text is None else int(seed_text))

    n, a, ops = random.choice(GENERATORS)()
    m = len(ops)

    print(n, m)
    print(" ".join(str(v) for v in a))
    for l, r, x in ops:
        print(l, r, x)


if __name__ == "__main__":
    main()
