#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 12:56
# update_at: 2026-09-29 12:56

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    numerator = next(data)
    denominator = next(data)
    # / 是真除法：直接把整数商舍入到最近的 double（与 C++ 的 1.0*a/b 同语义）
    # :.9f 固定小数位输出，把 double 的精确二进制值四舍五入到 9 位十进制小数
    print(f"{numerator / denominator:.9f}")


if __name__ == "__main__":
    solve()
