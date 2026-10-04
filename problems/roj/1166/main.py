#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:39
# update_at: 2026-09-29 21:39

import sys
from math import sqrt


def solve() -> None:
    """读入 x 与嵌套层数 n，按内层到外层展开 f(x,n) 并保留两位小数。"""
    x, n = map(float, sys.stdin.buffer.read().split())

    total = sqrt(1 + x)  # 最内层 f(x,1) = sqrt(1+x)，之后每层只看下一层的值
    for k in range(2, int(n) + 1):  # 外层 k 从 2 加到 n，把 sqrt(k + 下一层) 折叠进去
        total = sqrt(k + total)

    print(f"{total:.2f}")


if __name__ == "__main__":
    solve()
