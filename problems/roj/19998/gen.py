#!/usr/bin/env python3
"""gen.py：C. yet LIS 的小数据生成器，用于对拍。

输出格式与题目一致：
第一行 k n（k 在前，n 在后）
接下来 n 行，每行 k 个已排序的候选值（允许相等），值在 [0, 10]。
限制 n <= 8, k <= 5，保证暴力 k^n 枚举可行。
"""
import random
import sys

def main():
    seed = sys.argv[1] if len(sys.argv) > 1 else str(random.randrange(10**9))
    rng = random.Random(seed)

    n = rng.randint(1, 8)
    k = rng.randint(1, 5)

    print(k, n)
    for _ in range(n):
        row = sorted(rng.randint(0, 10) for _ in range(k))
        print(*row)

if __name__ == "__main__":
    main()