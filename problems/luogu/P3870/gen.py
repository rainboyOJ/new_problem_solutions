#!/usr/bin/env python3
"""生成 P3870 小数据：n 盏灯，m 个区间翻转 / 查询操作，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(1, 30)
    m = random.randint(1, 100)
    print(n, m)
    for _ in range(m):
        c = random.randint(0, 1)
        a = random.randint(1, n)
        b = random.randint(1, n)
        if a > b:
            a, b = b, a
        print(c, a, b)


if __name__ == "__main__":
    main()
