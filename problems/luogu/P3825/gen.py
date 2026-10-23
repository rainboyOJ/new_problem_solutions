#!/usr/bin/env python3
"""P3825 随机数据生成器。

小规模数据用于和 brute.cpp 对拍（枚举 3^n）；
设置环境变量 GEN_BIG=1 时生成接近满规模的数据，用来量性能。

对拍时 duipai.py 会传入 DUPAI_SEED / DUPAI_CASE_ID，用它播种保证可复现。
"""

import os
import random
import sys


def gen_small(rng):
    r = rng.random()
    if r < 0.30:
        return gen_satisfiable(rng)
    if r < 0.50:
        return gen_tight(rng)
    n = rng.randint(1, 8)
    # x 型地图张数：部分用例强制 d=0，其余在 1..min(n,8) 之间随机
    if rng.random() < 0.35:
        d = 0
    else:
        d = rng.randint(1, min(n, 8))
    positions = rng.sample(range(n), d)
    chars = []
    for i in range(n):
        if i in positions:
            chars.append("x")
        else:
            chars.append(rng.choice("abc"))
    m = rng.randint(0, 12)
    lines = [f"{n} {d}", "".join(chars), str(m)]
    for _ in range(m):
        i = rng.randint(1, n)
        j = rng.randint(1, n)
        hi = rng.choice("ABC")
        hj = rng.choice("ABC")
        lines.append(f"{i} {hi} {j} {hj}")
    return "\n".join(lines) + "\n"


def gen_satisfiable(rng):
    """先随机生成一组合法解，再只发与它相容的规则，保证实例一定有解。
    这类数据能检验「有解时是否真的输出合法方案」，是小数据对拍里最容易漏的一档。"""
    n = rng.randint(1, 8)
    d = rng.randint(0, min(n, 5))
    positions = rng.sample(range(n), d)
    chars = []
    forb = []
    for i in range(n):
        if i in positions:
            chars.append("x")
            forb.append(None)
        else:
            f = rng.randrange(3)
            chars.append("abc"[f])
            forb.append(f)
    sol = []
    for i in range(n):
        choices = [c for c in range(3) if c != forb[i]]
        sol.append(rng.choice(choices))
    m = rng.randint(1, 14)
    lines = [f"{n} {d}", "".join(chars), str(m)]
    for _ in range(m):
        style = rng.random()
        i = rng.randrange(n)
        j = rng.randrange(n)
        if style < 0.5:
            ci, cj = sol[i], sol[j]
        elif style < 0.75:
            false_premises = [c for c in range(3) if c != forb[i] and c != sol[i]]
            if not false_premises:
                ci, cj = sol[i], sol[j]
            else:
                ci, cj = rng.choice(false_premises), rng.randrange(3)
        else:
            ci, cj = sol[i], rng.randrange(3)
        lines.append(f"{i + 1} {chr(65 + ci)} {j + 1} {chr(65 + cj)}")
    return "\n".join(lines) + "\n"


def gen_tight(rng):
    """让每场比赛都出现在规则里，并且规则的车都选得「可用」，
    这样双方都必须真正做 2-SAT 推理，而不是被大量恒真规则带过去。"""
    n = rng.randint(2, 7)
    d = rng.randint(0, min(n, 3))
    positions = rng.sample(range(n), d)
    chars = []
    allowed = []
    for i in range(n):
        if i in positions:
            chars.append("x")
            allowed.append([0, 1, 2])
        else:
            f = rng.randrange(3)
            chars.append("abc"[f])
            allowed.append([c for c in range(3) if c != f])
    # 把 x 型地图先按枚举思路压成 2 个候选：真实取值随机挑 2 个
    for i in positions:
        allowed[i] = rng.sample([0, 1, 2], 2)
    m = rng.randint(n, 3 * n)
    lines = [f"{n} {d}", "".join(chars), str(m)]
    for _ in range(m):
        i = rng.randrange(n)
        j = rng.randrange(n)
        ci = rng.choice(allowed[i])
        cj = rng.choice(allowed[j])
        lines.append(f"{i + 1} {chr(65 + ci)} {j + 1} {chr(65 + cj)}")
    return "\n".join(lines) + "\n"


def gen_big(rng):
    n = 50000
    d = 8
    positions = rng.sample(range(n), d)
    chars = ["x" if i in positions else rng.choice("abc") for i in range(n)]
    m = 100000
    lines = [f"{n} {d}", "".join(chars), str(m)]
    for _ in range(m):
        i = rng.randint(1, n)
        j = rng.randint(1, n)
        lines.append(f"{i} {rng.choice('ABC')} {j} {rng.choice('ABC')}")
    return "\n".join(lines) + "\n"


def main():
    seed = int(os.environ.get("DUPAI_SEED") or os.environ.get("GEN_SEED") or 0)
    case_id = int(os.environ.get("DUPAI_CASE_ID") or 0)
    if seed == 0:
        seed = random.randrange(1, 10**9)
    rng = random.Random(seed * 1000003 + case_id)

    if os.environ.get("GEN_BIG") == "1":
        sys.stdout.write(gen_big(rng))
    else:
        sys.stdout.write(gen_small(rng))


if __name__ == "__main__":
    main()
