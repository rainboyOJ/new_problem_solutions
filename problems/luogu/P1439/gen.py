#!/usr/bin/env python3
"""小数据生成器：随机生成 n 和两个 1..n 的排列，方便 brute.cpp 做 2^n 枚举。"""
import random
import sys


def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
    random.seed(seed)

    n = random.randint(1, 15)

    p1 = list(range(1, n + 1))
    p2 = list(range(1, n + 1))
    random.shuffle(p1)
    random.shuffle(p2)

    print(n)
    print(" ".join(map(str, p1)))
    print(" ".join(map(str, p2)))


if __name__ == "__main__":
    main()
