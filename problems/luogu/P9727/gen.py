#!/usr/bin/env python3
"""P9727 随机数据生成器（输出到 stdout）。

约束来自题面：2 <= n, m <= 1000，sum(n*m) <= 1e6，T <= 1e3。
对拍时暴力只能跑很小的盘面，所以默认模式只生成 n*m <= 36 的小数据；
`--big` 模式生成贴满约束的大数据，用于检查正解不会崩（不参与对拍）。
"""
import random
import sys


def gen_small(rng):
    """小数据：n*m <= 36，覆盖 2..6 的全部边长与边界情形。"""
    cases = []
    # 先把所有边长的边界组合都覆盖一遍
    for n in range(2, 7):
        for m in range(2, 7):
            if n * m <= 36:
                cases.append((n, m))
    rng.shuffle(cases)
    cases = cases[: rng.randint(6, 10)]
    # 再补几个瘦长条（2 x k、3 x k 是构造里需要特判的情形）
    for _ in range(rng.randint(2, 4)):
        a = rng.randint(2, 3)
        b = rng.randint(4, 12)
        if a * b <= 36:
            cases.append((a, b) if rng.random() < 0.5 else (b, a))
    rng.shuffle(cases)
    return cases


def gen_big(rng):
    """大数据：贴满 sum(n*m) <= 1e6，边长到 1000，包含 4 的倍数的边界。"""
    cases = []
    total = 0
    options = [2, 3, 4, 5, 6, 7, 8, 999, 1000, 998, 500, 250]
    while total < 1000000:
        n = rng.choice(options)
        m = rng.choice(options)
        if total + n * m > 1000000:
            n = max(2, min(n, 1000))
            m = max(2, min(m, (1000000 - total) // n))
            if m < 2:
                break
        cases.append((n, m))
        total += n * m
        if len(cases) >= 1000:
            break
    return cases


def main():
    args = [a for a in sys.argv[1:] if a != "--big"]
    big = "--big" in sys.argv
    # 第一个参数是可选的“轮次”，用来在同一次对拍里生成不同批次的数据；
    # 不给参数时用固定种子，保证单次运行完全可复现。
    round_no = int(args[0]) if args else 0
    seed = 20221003 + round_no * 1000003
    rng = random.Random(seed)

    cases = gen_big(rng) if big else gen_small(rng)

    out = [str(len(cases))]
    for n, m in cases:
        out.append(f"{n} {m}")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
