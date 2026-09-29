#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 18:16
# update_at: 2026-09-29 18:20

import sys
from itertools import accumulate
from operator import mul


def solve() -> None:
    n = int(input())

    # accumulate 依次产出 1!, 2!, ..., n!（前缀积），对每项取倒数累加，再加首项 1
    e = 1.0 + sum(1.0 / f for f in accumulate(range(1, n + 1), mul))

    print(f"{e:.10f}")


if __name__ == "__main__":
    solve()
