#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 05:50
# update_at: 2026-10-01 05:50

import sys
from functools import reduce
from math import gcd

# 不可表示数的上界：互质的 a,b 最大凑不出的数是 ab-1，盒容量 ≤ 256，故 256*256 内必出答案
LIMIT = 256 * 256


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    boxes = [next(data) for _ in range(n)]

    # 所有盒容量的公约数 g>1 时，买到的块数永远是 g 的倍数，其余需求无限多且都没有最大者
    if reduce(gcd, boxes) != 1:
        print(0)
        return

    # 可达性筛：s 块能凑出 ⇔ 存在盒子 b，使 s-b 块能凑出（0 块是唯一初始事实）
    reachable = bytearray(LIMIT + 1)
    reachable[0] = 1
    for s in range(1, LIMIT + 1):
        reachable[s] = any(b <= s and reachable[s - b] for b in boxes)

    # 找不到不可表示的数说明范围内全能凑出，输出 0
    print(max((s for s in range(1, LIMIT + 1) if not reachable[s]), default=0))


if __name__ == "__main__":
    solve()
