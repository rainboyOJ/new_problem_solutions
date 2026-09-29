#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 18:05
# update_at: 2026-09-29 18:05

import sys

LANDINGS = 10  # 题面固定的落地次数


def solve() -> None:
    h = float(next(sys.stdin))  # 初始高度

    # 总路程 = 初始下落 h + 前 9 次反弹的往返（第 i 次反弹高度为 h / 2^i，往返各一次）
    total = h + sum(h / 2**i * 2 for i in range(1, LANDINGS))

    # 输出格式对齐 C++ 的 cout 默认行为：6 位有效数字、去掉多余末尾 0，即 %g
    print("%g" % total)
    print("%g" % (h / 2**LANDINGS))  # 第 10 次反弹的高度


if __name__ == "__main__":
    solve()
