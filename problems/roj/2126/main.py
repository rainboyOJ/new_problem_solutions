#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 07:42
# update_at: 2026-10-08 07:42

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    # 通道忽略方向是最少的 N-1 条 ⇒ 底图是树，有向定向不可能有环，
    # 每个站顺着出边走必然停在出度为 0 的站（sink）。
    edges = [(next(data), next(data)) for _ in range(n - 1)]
    sinks = set(range(1, n + 1)) - {start for start, _end in edges}  # 出度为 0 的站
    sink_count = len(sinks)
    # sink 多于一个 ⇒ 谁也到不了别的 sink；恰好一个 ⇒ 全图都汇入它，它即答案
    print(min(sinks) if sink_count == 1 else -1)


if __name__ == "__main__":
    solve()
