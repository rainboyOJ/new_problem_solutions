#!/usr/bin/env python3
"""P9244 随机数据生成器：输出到 stdout。

格式：
    第一行 K
    第二行 S c1 c2   （S 与两个字符之间用空格分隔）

用法：
    python3 gen.py              # 使用默认固定种子，结果可复现
    python3 gen.py <seed>       # 指定种子，方便对拍时覆盖更多情形
    GEN_SEED=<seed> python3 gen.py

注意：为了让 brute.cpp 的 O(n^2) 枚举能在对拍中跑完，
      n 始终控制在 2000 以内。
"""
import os
import random
import sys

DEFAULT_SEED = 9244


def make_case(seed):
    """根据 seed 挑选一种构造模式，返回 (K, S, c1, c2)。"""
    mode = seed % 8

    if mode == 0:
        # 极小边界：n = 2, K = 2，只有一个候选子串
        n = 2
        K = 2
        S = "".join(random.choice("ab") for _ in range(n))
        c1, c2 = "a", "b"

    elif mode == 1:
        # K 恰好等于 n，只有整个串这一个候选子串
        n = random.randint(2, 30)
        K = n
        S = "".join(random.choice("ab") for _ in range(n))
        c1, c2 = "a", "b"

    elif mode == 2:
        # 全同字符 + c1 == c2，答案最大，检验计数是否漏算/重算
        n = random.randint(2, 60)
        K = random.randint(2, n)
        S = "a" * n
        c1 = c2 = "a"

    elif mode == 3:
        # 单字符集，c1 不存在，答案必须为 0
        n = random.randint(2, 40)
        K = random.randint(2, n)
        S = "b" * n
        c1, c2 = "a", "b"

    elif mode == 4:
        # 小字符集：答案往往很大，覆盖计数累积
        n = random.randint(2, 120)
        K = random.randint(2, n)
        S = "".join(random.choice("ab") for _ in range(n))
        c1, c2 = "a", "b"

    elif mode == 5:
        # 完整小写字母表，c1、c2 从串中真实出现过的字符里挑
        n = random.randint(2, 200)
        K = random.randint(2, n)
        S = "".join(random.choice("abcdefghijklmnopqrstuvwxyz") for _ in range(n))
        c1 = random.choice(S)
        c2 = random.choice(S)

    elif mode == 6:
        # 字符集较大但 n 也较大，答案适中，检验一般情形
        n = random.randint(500, 1000)
        K = random.randint(2, n)
        S = "".join(random.choice("abcde") for _ in range(n))
        c1, c2 = "a", "b"

    else:
        # 较长串 + 极小 K（K = 2），起点集合几乎立刻被填满
        n = random.randint(1500, 2000)
        K = 2
        S = "".join(random.choice("abc") for _ in range(n))
        c1, c2 = "a", "c"

    return K, S, c1, c2


def main():
    if len(sys.argv) > 1:
        seed = int(sys.argv[1])
    else:
        seed = int(os.environ.get("GEN_SEED", DEFAULT_SEED))
    random.seed(seed)

    K, S, c1, c2 = make_case(seed)

    print(K)
    print(S, c1, c2)


if __name__ == "__main__":
    main()
