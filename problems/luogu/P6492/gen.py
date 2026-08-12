#!/usr/bin/env python3
"""生成 P6492 小数据：初始全 L 的长度 n 序列，q 次单点翻转，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    q = random.randint(1, 100)
    print(n, q)
    for _ in range(q):
        print(random.randint(1, n))


if __name__ == "__main__":
    main()
