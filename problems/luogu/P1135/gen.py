#!/usr/bin/env python3
"""生成 P1135 小数据：随机楼层数 n、每层数字 k[i]、起点 A 和终点 B，规模适合暴力对拍。"""
import random

random.seed()


def main():
    n = random.randint(1, 12)
    s = random.randint(1, n)
    t = random.randint(1, n)
    print(n, s, t)
    print(*[random.randint(0, n) for _ in range(n)])


if __name__ == "__main__":
    main()
