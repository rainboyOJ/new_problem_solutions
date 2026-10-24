#!/usr/bin/env python3
"""生成 P5536 小数据：随机树 + 随机 k，规模适合 01 序列枚举暴力。"""
import random
import sys


def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
    random.seed(seed)
    n = random.randint(2, 12)
    k = random.randint(1, n - 1)
    print(n, k)
    for i in range(2, n + 1):
        # 偏好生成链或星形，让边界结构更容易被覆盖
        style = random.random()
        if style < 0.3:
            print(i, i - 1)             # 链
        elif style < 0.45:
            print(i, 1)                 # 星
        else:
            print(i, random.randint(1, i - 1))


if __name__ == "__main__":
    main()
