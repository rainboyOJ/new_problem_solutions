#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:46
# update_at: 2026-10-04 10:11

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)                            # 人数 n 可以为 0，此时没有成绩
    scores = (next(data) for _ in range(n))   # 顺序消费恰好 n 个成绩，惰性产出、不建中间列表
    print(max(scores, default=0))             # 成绩非负，空序列的最高分按 0 计


if __name__ == "__main__":
    solve()
