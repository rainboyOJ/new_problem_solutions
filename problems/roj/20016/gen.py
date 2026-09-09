#!/usr/bin/env python3
"""A. Glass 随机数据生成器。

生成 n 个点 (x, y)，坐标在 [1, 1e8]。
约 10% 概率生成退化数据：所有点重合（min == max），
用来覆盖"罩子恰好包住一个点"的边界情况。
"""
import random

random.seed()


def main():
    n = random.randint(2, 200000)
    print(n)
    if random.random() < 0.1:
        x = random.randint(1, 10**8)
        y = random.randint(1, 10**8)
        for _ in range(n):
            print(x, y)
    else:
        for _ in range(n):
            print(random.randint(1, 10**8), random.randint(1, 10**8))


if __name__ == "__main__":
    main()