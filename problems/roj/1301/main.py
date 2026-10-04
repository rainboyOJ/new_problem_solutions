#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 04:00
# update_at: 2026-09-30 04:00

import sys
from collections.abc import Iterator


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n = next(data)
        vals: Iterator[int] = (next(data) for _ in range(n))

        # 滚动 DP：prev2 = f[i-2]，prev1 = f[i-1]，当前格可选可不选。
        prev2, prev1 = 0, next(vals) if n else 0
        for x in vals:
            prev2, prev1 = prev1, max(prev1, prev2 + x)

        out.append(str(prev1))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
