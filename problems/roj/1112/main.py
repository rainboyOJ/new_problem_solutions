#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:27
# update_at: 2026-09-29 19:27

import sys


def solve() -> None:
    """输出 M 个整数的极差：最大值减最小值。

    第一行的 M 只声明后面有几个数，解包时保留名字；余下的整数一次交给内置
    max/min，两者各扫一遍列表，因此额外空间是一份 O(M) 的输入表。
    """
    m, *values = map(int, sys.stdin.buffer.read().split())
    print(max(values) - min(values))


if __name__ == "__main__":
    solve()
