#!/usr/bin/env python3
"""AcWing 1018 最低通行费 的随机小数据生成器（配合 brute.cpp 对拍，n 保持很小）。"""

import random


def main():
    random.seed()
    n = random.randint(1, 7)
    print(n)
    for _ in range(n):
        print(" ".join(str(random.randint(1, 20)) for _ in range(n)))


if __name__ == "__main__":
    main()
