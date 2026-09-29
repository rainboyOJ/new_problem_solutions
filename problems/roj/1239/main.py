#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:12
# update_at: 2026-09-30 01:12

import sys
from collections import Counter


def solve() -> None:
    """读入所有数字，统计频次后按数值升序输出。"""
    data = map(int, sys.stdin.buffer.read().split())
    n = next(data)                                  # 自然数个数
    counts = Counter(data)                            # 每个数字的出现次数
    out = '\n'.join(f'{v} {c}' for v, c in sorted(counts.items()))
    sys.stdout.write(out)


if __name__ == "__main__":
    solve()
