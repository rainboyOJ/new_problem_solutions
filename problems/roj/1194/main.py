#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:50
# update_at: 2026-09-29 22:50

from math import comb


def solve() -> None:
    m, n = map(int, input().split())
    # 任一条路线都恰含 m-1 步"上"与 n-1 步"右"，路线只由这 m+n-2 步的顺序决定：
    # 在总步数里任选 m-1 个位置放"上"，其余放"右"，故答案为组合数。
    print(comb(m + n - 2, m - 1))


if __name__ == "__main__":
    solve()
