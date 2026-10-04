#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:26
# update_at: 2026-09-29 19:26

import sys
from collections import Counter


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 数组大小：只用于界定输入流，计数本身不需要它
    freq = Counter(data)  # 桶排思想：每个数出现几次就往对应桶里加一

    top = max(freq)  # 只统计到数组里最大的数为止
    # 从 0 逐桶输出，没出现过的桶 Counter 里查不到，补 0
    counts = (freq.get(x, 0) for x in range(top + 1))
    print('\n'.join(map(str, counts)))


if __name__ == "__main__":
    solve()
