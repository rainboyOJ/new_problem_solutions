#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 13:51
# update_at: 2026-10-04 14:10


import sys


def solve() -> None:
    # 单精度浮点数读入后用 %.3f 格式化：四舍五入保留 3 位小数
    data = iter(map(float, sys.stdin.buffer.read().split()))
    x = next(data)
    print(f"{x:.3f}")


if __name__ == "__main__":
    solve()
