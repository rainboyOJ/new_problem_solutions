#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:33
# update_at: 2026-09-30 07:33

import sys
from heapq import heappush, heappop


def solve() -> None:
    """用大根堆维护排队患者：pop 输出优先级最大者，空队输出 none。"""
    data = iter(sys.stdin.read().split())
    out: list[str] = []
    heap: list[tuple[int, str]] = []  # 存 (-优先级, 姓名)：Python 只有最小堆，优先级取负即变大根堆

    for _ in range(int(next(data))):
        op = next(data)
        if op == "push":
            name, priority = next(data), int(next(data))
            heappush(heap, (-priority, name))  # 优先级互不相同，元组比较不会走到姓名
        elif heap:
            neg_priority, name = heappop(heap)
            out.append(f"{name} {-neg_priority}")
        else:
            out.append("none")

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
