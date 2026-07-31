#!/usr/bin/env python3
"""CSP201312C 的小数据随机生成器，供单调栈解与暴力解对拍。"""

import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    n = random.randint(1, 30)
    heights = [random.randint(1, 50) for _ in range(n)]

    print(n)
    print(*heights)


if __name__ == "__main__":
    main()
