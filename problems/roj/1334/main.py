#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:43
# update_at: 2026-09-30 05:43

import sys
from collections import deque


def josephus(n: int, m: int) -> list[str]:
    """模拟围圈报数，返回出列顺序。"""
    q: deque[int] = deque(range(1, n + 1))
    ans: list[str] = []
    cnt = 0
    while q:
        x = q.popleft()
        cnt += 1
        if cnt == m:
            ans.append(str(x))
            cnt = 0
        else:
            q.append(x)
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    print(' '.join(josephus(n, m)))


if __name__ == "__main__":
    solve()
