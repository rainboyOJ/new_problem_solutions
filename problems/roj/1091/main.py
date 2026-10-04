#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 18:16
# update_at: 2026-09-29 18:16

import sys
from itertools import accumulate


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0] if data else 0
    # 阶乘递推：f_i = i * f_{i-1}，前缀和：s_i = s_{i-1} + f_i
    facts = accumulate(range(1, n + 1), lambda f, i: f * i, initial=1)  # 初始 f_0 = 1
    print(sum(facts) - 1)  # 去掉多余的 0! = 1


if __name__ == "__main__":
    solve()
