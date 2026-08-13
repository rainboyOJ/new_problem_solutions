#!/usr/bin/env python3
"""随机生成小规模数据：n <= 8，坐标在 [-20, 20] 内（最多 3 位小数）。

n! 种吃奶酪顺序，n=8 时只有 40320 种，brute.cpp 全排列枚举可以瞬间跑完，
适合与 main.cpp 做随机对拍。
"""
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 8)
    print(n)
    for _ in range(n):
        x = random.uniform(-20, 20)
        y = random.uniform(-20, 20)
        print(f"{x:.3f} {y:.3f}")


if __name__ == "__main__":
    main()
