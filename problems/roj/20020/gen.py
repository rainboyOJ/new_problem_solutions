#!/usr/bin/env python3
"""gen.py：随机生成小数据用于对拍。
n <= 15，a_i < 2^6（6 位），保证至少有一个 0 值，便于覆盖空集合或为 0 的边界。
"""
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    n = random.randint(1, 15)
    a = [random.randint(0, 63) for _ in range(n)]
    a[random.randrange(n)] = 0  # 保证出现 0
    print(n)
    print(" ".join(map(str, a)))


if __name__ == "__main__":
    main()
