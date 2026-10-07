#!/usr/bin/env python3
"""gen.py：B. Color 小数据随机生成器（与 main.cpp / brute.cpp 相同输入格式）。

生成 n,m <= 10、a <= 15 的小数据，供 main.cpp 与 brute.cpp 对拍。
"""

import random
import sys


def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else 0
    random.seed(seed)

    T = random.randint(1, 5)
    print(T)
    for _ in range(T):
        n = random.randint(1, 10)
        m = random.randint(1, 10)
        a = random.randint(1, 15)
        print(a, n, m)
        nums = [random.randint(1, n * m) for _ in range(a)]
        print(" ".join(map(str, nums)))


if __name__ == "__main__":
    main()