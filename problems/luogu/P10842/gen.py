#!/usr/bin/env python3
# gen.py：为 P10842 生成随机小树（n 小，便于暴力对拍）。
import random


def main():
    random.seed()
    n = random.randint(2, 8)
    print(n)
    # 随机生成一棵树：每个点 i 从 1..i-1 中随机选父亲
    for i in range(2, n + 1):
        fa = random.randint(1, i - 1)
        print(fa, i)


if __name__ == "__main__":
    main()
