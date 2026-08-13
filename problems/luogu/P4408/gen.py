#!/usr/bin/env python3
"""生成 P4408 小数据：随机树 + 随机边权（含 0），规模适合三点枚举暴力。"""
import random

random.seed()


def main():
    n = random.randint(3, 10)
    print(n, n - 1)
    for i in range(2, n + 1):
        print(i, random.randint(1, i - 1), random.randint(0, 10))


if __name__ == "__main__":
    main()
