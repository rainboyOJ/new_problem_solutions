#!/usr/bin/env python3
"""生成 P2895 小数据：m 颗流星 (x, y, t)，坐标与时间都小，适合暴力对拍。"""
import random

random.seed()


def main():
    m = random.randint(1, 12)
    print(m)
    for _ in range(m):
        x = random.randint(0, 15)
        y = random.randint(0, 15)
        t = random.randint(0, 25)
        print(x, y, t)


if __name__ == "__main__":
    main()
