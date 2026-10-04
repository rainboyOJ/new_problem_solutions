#!/usr/bin/env python3
"""P9719 数据生成器。

用法：python3 gen.py [seed]  （结果输出到 stdout，seed 省略时用默认值）

两类数据交替生成：
  1. 由随机串 s 反推出合法的 p 数组（保证有解，用来检验最小字典序答案）；
  2. 完全随机的 p 数组（大多数无解，用来检验 -1 判定）。
同时覆盖 n=1、全 1、p_i=i 等边界。
固定随机种子，保证可复现。
"""
import random
import sys

SEED = 20229719


def compute_p(s):
    """朴素 O(n^2) 求出串 s（下标 0 起）每个前缀的最小后缀起点 p_i（1 起）。"""
    n = len(s)
    p = []
    for j in range(n):
        best = 0
        for x in range(1, j + 1):
            a, b = x, best
            while a <= j and b <= j and s[a] == s[b]:
                a += 1
                b += 1
            if b > j:
                continue          # best 段是 x 段的前缀，更短者更小 -> best 胜
            if a > j:
                best = x          # x 段更短 -> x 胜
            elif s[a] < s[b]:
                best = x
        p.append(best + 1)
    return p


def gen_test(rng):
    mode = rng.random()
    if mode < 0.45:
        # 由随机串反推 p，保证有解
        n = rng.randint(1, 7)
        k = rng.randint(1, min(3, n))
        s = [rng.randint(1, k) for _ in range(n)]
        p = compute_p(s)
        return n, p
    if mode < 0.60:
        # 纯随机 p，多为无解
        n = rng.randint(1, 7)
        p = [rng.randint(1, i) for i in range(1, n + 1)]
        return n, p
    if mode < 0.72:
        # 全 1
        n = rng.randint(1, 7)
        return n, [1] * n
    if mode < 0.84:
        # p_i = i
        n = rng.randint(1, 7)
        return n, list(range(1, n + 1))
    if mode < 0.92:
        # 后半段全 1 的混合
        n = rng.randint(2, 7)
        p = [rng.randint(1, i) for i in range(1, n + 1)]
        p[-1] = 1
        return n, p
    # 单字符
    return 1, [1]


def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else SEED
    rng = random.Random(seed)
    T = rng.randint(1, 5)
    tests = [gen_test(rng) for _ in range(T)]
    out = [str(T)]
    for n, p in tests:
        out.append(str(n))
        out.append(" ".join(map(str, p)))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
