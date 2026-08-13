#!/usr/bin/env python3
"""生成随机树网数据：随机树 + 随机边权 + 随机 s。

n 控制在 12 以内，使 brute.cpp 的全源距离 + 区间枚举暴力能在小数据下跑完，
作为与 main.cpp 对拍的基准。
"""
import random


def main():
    random.seed()
    n = random.randint(2, 12)
    s = random.randint(0, 20)
    print(n, s)
    for v in range(2, n + 1):
        u = random.randint(1, v - 1)
        w = random.randint(1, 10)
        print(u, v, w)


if __name__ == "__main__":
    main()
