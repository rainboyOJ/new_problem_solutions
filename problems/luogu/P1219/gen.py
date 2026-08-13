#!/usr/bin/env python3
"""生成 P1219 小数据：单个整数 n，表示棋盘大小。

n 限制在 [1, 10]：brute.cpp 是全排列枚举再检查的暴力，
实测 n=10 约 0.4s，n=11 已需要约 4s，再大不适合对拍。
n=11..13 的正确性另外用 main.py 交叉验证已知解数。
"""

import random

random.seed()


def main():
    print(random.randint(1, 10))


if __name__ == "__main__":
    main()
