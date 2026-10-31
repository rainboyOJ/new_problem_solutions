#!/usr/bin/env python3
"""对拍数据生成器：n 个非负整数，从中选恰好 m 个。

模式由第一个命令行参数或环境变量 GEN_MODE 指定（duipai.py 不给生成器传参，
所以需要定向对拍时用 `GEN_MODE=drop duipai.py ...`）。不指定时随机出题。
"""
import os
import sys

from cyaron import randint


def emit(a, m):
    print(len(a), m)
    print(*a)


def mode_name():
    if len(sys.argv) > 1:
        return sys.argv[1]
    return os.environ.get("GEN_MODE", "rand")


def main():
    mode = mode_name()
    if mode == "min":                     # 最小规模：n = m = 1
        emit([randint(0, 3)], 1)
        return
    if mode == "onerange":                # m = 1，答案就是最大值
        n = randint(1, 12)
        emit([randint(0, 63) for _ in range(n)], 1)
        return
    if mode == "all":                     # m = n，答案就是全部数的与
        n = randint(1, 12)
        emit([randint(0, 63) for _ in range(n)], n)
        return
    if mode == "pair":                    # m = 2，答案来自某个数对
        n = randint(2, 12)
        emit([randint(0, 63) for _ in range(n)], 2)
        return
    if mode == "drop":                    # m = n - 1，恰好丢掉一个数
        n = randint(2, 13)
        emit([randint(0, 63) for _ in range(n)], n - 1)
        return
    if mode == "allones":                 # 特殊性质 A：每个数都是 2^k - 1
        n = randint(1, 13)
        m = randint(1, n)
        emit([(1 << randint(0, 10)) - 1 for _ in range(n)], m)
        return
    if mode == "smallval":                # 小值域：a_i < 2^10
        n = randint(1, 13)
        m = randint(1, n)
        hi = (1 << randint(1, 10)) - 1
        emit([randint(0, hi) for _ in range(n)], m)
        return
    if mode == "narrow":                  # 位宽很小，容易产生相同结果
        n = randint(2, 12)
        m = randint(1, n)
        emit([randint(0, 3) for _ in range(n)], m)
        return
    if mode == "zero":                    # 大量 0，答案必为 0
        n = randint(1, 12)
        m = randint(1, n)
        emit([0 if randint(0, 1) == 0 else randint(0, 15) for _ in range(n)], m)
        return
    if mode == "bigdrop":                 # 满规模 + m = n - 1
        n = 200000
        emit([randint(0, (1 << 20) - 1) for _ in range(n)], n - 1)
        return
    if mode == "bigsmall":                # 满规模 + 小值域，给值域压缩层压测用
        n = 200000
        m = randint(1, n)
        hi = (1 << randint(8, 20)) - 1
        emit([randint(0, hi) for _ in range(n)], m)
        return
    if mode == "bigallones":              # 满规模 + 特殊性质 A
        n = 200000
        m = randint(1, n)
        emit([(1 << randint(0, 19)) - 1 for _ in range(n)], m)
        return
    if mode == "bigfull":                 # 满规模 + 完整值域 2^30
        n = 200000
        m = randint(1, n)
        emit([randint(0, (1 << 30) - 1) for _ in range(n)], m)
        return

    n = randint(1, 12)
    m = randint(1, n)
    hi = (1 << randint(1, 10)) - 1
    emit([randint(0, hi) for _ in range(n)], m)


if __name__ == "__main__":
    main()
