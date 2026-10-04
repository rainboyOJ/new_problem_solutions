#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2025-11-28 15:41
# update_at: 2025-11-28 15:41

import sys


def solve() -> None:
    data = iter(map(float, sys.stdin.buffer.read().split()))
    n = int(next(data))
    vals = [next(data, 0.0) for _ in range(n)]  # 同步 std.cpp 读到 EOF 后的零填充

    mx, mn = max(vals), min(vals)
    avg = (sum(vals) - mx - mn) / (n - 2)
    err = max(abs(x - avg) for x in vals if x not in (mx, mn))

    print(f"{avg:.2f} {err:.2f}")


if __name__ == "__main__":
    solve()
