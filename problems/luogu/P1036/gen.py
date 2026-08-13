#!/usr/bin/env python3
"""生成 P1036 小数据：n 个数、选 k 个求和判素数，规模适合 01 序列暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(2, 15)
    k = random.randint(1, n - 1)
    print(n, k)
    print(*[random.randint(1, 100) for _ in range(n)])


if __name__ == "__main__":
    main()
