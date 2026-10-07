#!/usr/bin/env python3
# gen.py：T5 好序列 对拍小数据生成器
# n <= 8，a_i <= 5，保证逐位枚举暴力 (brute.cpp) 能跑完（最坏 5^8 种序列）。
import random
import sys


def main():
    seed = sys.argv[1] if len(sys.argv) > 1 else None
    if seed is not None:
        random.seed(int(seed))
    n = random.randint(1, 8)
    a = [random.randint(1, 5) for _ in range(n)]
    print(n)
    print(" ".join(map(str, a)))


if __name__ == "__main__":
    main()