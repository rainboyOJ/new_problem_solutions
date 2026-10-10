#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 02:01
# update_at: 2026-10-09 02:01

import sys


def solve() -> None:
    """读入头数 x、脚数 y，按「鸡 兔」顺序输出各自数量（与 C++ 侧同一公式）。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    x = next(data, None)  # 头的数量；无输入则静默退出，与 C++ 侧 cin 失败的行为一致
    if x is None:
        return
    y = next(data, None)
    if y is None:
        return
    chicken = (4 * x - y) // 2  # 鸡：每只 2 只脚
    rabbit = (y - 2 * x) // 2   # 兔：每只 4 只脚
    print(chicken, rabbit)


if __name__ == "__main__":
    solve()
