#!/usr/bin/env python3
"""gen.py：T1. 画 小数据随机生成器（与 main.cpp / brute.cpp 相同输入格式）。

生成 n,m 为 3 的倍数（3 <= n,m <= 30）的随机 R/G/B 像素矩阵，
供 main.cpp 与 brute.cpp 对拍。
"""

import os
import random
import sys

COLORS = "RGB"
SIZES = [3, 6, 9, 12, 15, 18, 21, 24, 27, 30]


def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else int(os.environ.get("DUPAI_SEED", "0"))
    random.seed(seed)

    n = random.choice(SIZES)
    m = random.choice(SIZES)
    print(n, m)
    for _ in range(n):
        print("".join(random.choice(COLORS) for _ in range(m)))


if __name__ == "__main__":
    main()