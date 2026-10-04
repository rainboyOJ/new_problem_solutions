#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 13:19
# update_at: 2026-09-29 13:19

import sys


def solve() -> None:
    r1, r2 = map(float, sys.stdin.buffer.read().split())
    # 并联公式 R = 1/(1/r1 + 1/r2) = r1*r2/(r1+r2)，通分后少一次除法
    resistance = r1 * r2 / (r1 + r2)
    print(f"{resistance:.2f}")


if __name__ == "__main__":
    solve()
