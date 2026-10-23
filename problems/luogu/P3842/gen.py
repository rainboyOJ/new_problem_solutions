#!/usr/bin/env python3
"""为 P3842 生成小规模随机数据：每行一个区间 [L, R]，1 <= L <= R <= n。"""
import random


def main():
    random.seed()

    n = random.randint(1, 8)
    print(n)
    for _ in range(n):
        l = random.randint(1, n)
        r = random.randint(l, n)
        print(l, r)


if __name__ == "__main__":
    main()
