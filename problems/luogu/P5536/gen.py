#!/usr/bin/env python3
"""生成 P5536 小数据：随机树 + 随机 k，规模适合组合枚举暴力。"""
import random

random.seed()


def main():
    n = random.randint(2, 8)
    k = random.randint(1, n - 1)
    print(n, k)
    for i in range(2, n + 1):
        print(i, random.randint(1, i - 1))


if __name__ == "__main__":
    main()
