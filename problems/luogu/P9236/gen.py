#!/usr/bin/env python3
"""P9236 随机数据生成器：输出到 stdout。

用法：
    python3 gen.py              # 使用默认固定种子，结果可复现
    python3 gen.py <seed>       # 指定种子，方便对拍时覆盖更多情形
    GEN_SEED=<seed> python3 gen.py
"""
import os
import random
import sys

DEFAULT_SEED = 9236


def main():
    if len(sys.argv) > 1:
        seed = int(sys.argv[1])
    else:
        seed = int(os.environ.get("GEN_SEED", DEFAULT_SEED))
    random.seed(seed)
    mode = seed % 6

    if mode == 0:
        # 极小边界：n = 1
        n = 1
        values = [random.choice([0, 1, 2, 3])]
    elif mode == 1:
        # 含大量 0，用来检验 0 的异或不会影响结果
        n = random.randint(1, 12)
        values = [random.choice([0, 0, 0, 1, 2]) for _ in range(n)]
    elif mode == 2:
        # 小值域，容易产生重复的前缀异或（count0 * count1 会很大）
        n = random.randint(1, 15)
        values = [random.randint(0, 7) for _ in range(n)]
    elif mode == 3:
        # 中等规模，覆盖到 2^20 附近的数
        n = random.randint(20, 200)
        values = [random.randint(0, 1 << 20) for _ in range(n)]
    elif mode == 4:
        # 全部取到上界 2^20，检验最高位和溢出
        n = random.randint(1, 10)
        values = [1 << 20] * n
    else:
        # 稍大规模：仍然在暴力 O(n^2) 的承受范围内
        n = random.randint(100, 300)
        values = [random.randint(0, 1 << 20) for _ in range(n)]

    print(n)
    print(" ".join(str(v) for v in values))


if __name__ == "__main__":
    main()
