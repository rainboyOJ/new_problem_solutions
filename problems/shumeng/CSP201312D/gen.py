#!/usr/bin/env python3
"""CSP201312D 的小数据随机生成器，供计数 DP 与递归枚举对拍。"""

import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    test_count = random.randint(1, 3)
    print(test_count)
    for _ in range(test_count):
        # 4^11 约为 400 万，仍适合教学暴力程序。
        print(random.randint(1, 11))


if __name__ == "__main__":
    main()
