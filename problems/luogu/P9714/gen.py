#!/usr/bin/env python3
"""P9714 随机数据生成器。

用法：
    python3 gen.py [mode] [seed]

- mode 默认 small，生成暴力也能跑完的小数据（用于对拍）。
- 其它模式：yes / sym / boundary / large。
- seed 默认 9714，固定种子保证可复现；也可以传环境变量 P9714_SEED。

题面约束：1 <= sum n <= 2000，n >= 1，1 <= t_i, b_i <= 2000。
"""
import os
import random
import sys

DEFAULT_SEED = 9714
MAXV = 2000  # 题面：1 <= t_i, b_i <= 2000
MAX_SUM_N = 2000


def emit(cases):
    """按题目输入格式输出。"""
    out = [str(len(cases))]
    for n, t, b in cases:
        out.append(str(n))
        out.append(" ".join(map(str, t)))
        out.append(" ".join(map(str, b)))
    sys.stdout.write("\n".join(out) + "\n")


def gen_small(rng):
    """小 n + 小值：暴力可以完整搜索，是主要对拍数据。"""
    cases = []
    for _ in range(40):
        n = rng.randint(1, 4)
        t = [rng.randint(1, 4) for _ in range(n)]
        # 让 b 与 t 的量级相近，既有 Yes 也有 No，又不至于搜索过深
        hi = rng.choice([4, 8, 12, 20])
        b = [rng.randint(1, hi) for _ in range(n)]
        cases.append((n, t, b))
    return cases


def gen_yes_by_construction(rng):
    """按题面操作序列正向构造出一定能成功的 b，保证 Yes 数据不是全靠猜。"""
    cases = []
    while len(cases) < 25:
        n = rng.randint(1, 4)
        t = [rng.randint(1, 3) for _ in range(n)]
        cur_t = t[:]
        a = [0] * n
        steps = rng.randint(1, 5)
        for _ in range(steps):
            if rng.random() < 0.5:
                a = [a[i] + cur_t[i] for i in range(n)]
            else:
                cur_t = [cur_t[i] + cur_t[n - 1 - i] for i in range(n)]
        if min(a) < 1 or max(a) > 20:
            continue  # 题面要求 1 <= b_i，且值太大暴力会慢
        cases.append((n, t, a[:]))
    return cases


def gen_symmetric_t(rng):
    """t 完全对称的数据：此时解退化为 b_i / t_i 是否恒为一个整数。"""
    cases = []
    for _ in range(25):
        n = rng.randint(1, 4)
        t = [0] * n
        for i in range(n):
            mirror = n - 1 - i
            if i <= mirror:
                t[i] = rng.randint(1, 4)
            else:
                t[i] = t[mirror]
        k = rng.randint(1, 5)
        if rng.random() < 0.6:
            b = [t[i] * k for i in range(n)]
        else:
            b = [max(1, t[i] * k + rng.randint(-2, 2)) for i in range(n)]
        cases.append((n, t, b))
    return cases


def gen_boundary(rng):
    """边界：n = 1、全 1、最小值/最大值组合。"""
    cases = [
        (1, [1], [1]),
        (1, [1], [2]),
        (1, [2], [1]),
        (1, [4], [4]),
        (1, [4], [3]),
        (2, [1, 1], [4, 4]),
        (2, [1, 1], [4, 3]),
        (2, [1, 2], [4, 4]),
        (2, [2, 1], [4, 4]),
        (3, [1, 1, 1], [8, 8, 8]),
        (3, [2, 1, 2], [8, 8, 8]),
        (4, [1, 2, 3, 4], [20, 20, 20, 20]),
        (4, [4, 3, 2, 1], [1, 1, 1, 1]),
    ]
    # 再补一些 n 很小的随机数据
    for _ in range(20):
        n = rng.randint(1, 3)
        t = [rng.randint(1, 4) for _ in range(n)]
        b = [rng.randint(1, 10) for _ in range(n)]
        cases.append((n, t, b))
    return cases


def gen_large(rng):
    """大数据：贴着题面上限，用来检验 main.cpp 的复杂度和溢出。

    这类数据暴力跑不动，只用于检查 main.cpp 不崩、不超时。
    """
    cases = []
    total = 0
    while total < MAX_SUM_N:
        n = rng.randint(1, 300)
        if total + n > MAX_SUM_N:
            n = MAX_SUM_N - total
        total += n
        t = [rng.randint(1, MAXV) for _ in range(n)]
        if rng.random() < 0.3:
            # 让 t 对称，命中另一条分支
            for i in range(n):
                if i < n - 1 - i:
                    t[n - 1 - i] = t[i]
        b = [rng.randint(1, MAXV) for _ in range(n)]
        cases.append((n, t, b))
    # 再混入一组构造为 Yes 的大数据
    n = 300
    t = [rng.randint(1, 6) for _ in range(n)]
    cur_t = t[:]
    a = [0] * n
    for _ in range(4):
        if rng.random() < 0.5:
            a = [a[i] + cur_t[i] for i in range(n)]
        else:
            cur_t = [cur_t[i] + cur_t[n - 1 - i] for i in range(n)]
    if min(a) >= 1 and max(a) <= MAXV:
        cases.append((n, t, a[:]))
    return cases


def main():
    mode = sys.argv[1] if len(sys.argv) > 1 else "mix"
    seed = int(sys.argv[2]) if len(sys.argv) > 2 else int(os.environ.get("P9714_SEED", DEFAULT_SEED))
    rng = random.Random(seed)

    if mode == "small":
        cases = gen_small(rng)
    elif mode == "yes":
        cases = gen_yes_by_construction(rng)
    elif mode == "sym":
        cases = gen_symmetric_t(rng)
    elif mode == "boundary":
        cases = gen_boundary(rng)
    elif mode == "large":
        cases = gen_large(rng)
    else:
        # 默认模式：把全部「暴力能跑完」的数据混在一起，
        # 每次对拍都能同时覆盖随机小数据、构造 Yes、对称 t 和边界。
        cases = gen_small(rng) + gen_symmetric_t(rng) + gen_boundary(rng) + gen_yes_by_construction(rng)
        rng.shuffle(cases)

    emit(cases)


if __name__ == "__main__":
    main()
