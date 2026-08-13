#!/usr/bin/env python3
"""生成 P1351 小数据：随机树 n<=30，点权在 1..10000 随机，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(2, 30)
    print(n)
    # 依次把每个新点接到前面任意一个点上，生成一棵随机树。
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        print(parent, i)
    print(" ".join(str(random.randint(1, 10000)) for _ in range(n)))


if __name__ == "__main__":
    main()
