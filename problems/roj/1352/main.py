#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:35
# update_at: 2026-09-30 06:35

import sys
from collections import deque


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    # 约束 “a 比 b 高” 改写成 b -> a：沿这个方向拓扑排序，才能先定低薪再定高薪
    succ: list[list[int]] = [[] for _ in range(n + 1)]
    indeg = [0] * (n + 1)
    for _ in range(m):
        a, b = next(data), next(data)
        succ[b].append(a)
        indeg[a] += 1

    pay = [100] * (n + 1)  # 每位员工奖金最少 100 元
    q = deque(i for i in range(1, n + 1) if not indeg[i])
    done = 0
    while q:
        u = q.popleft()
        done += 1
        for v in succ[u]:
            pay[v] = max(pay[v], pay[u] + 1)  # 至少比更低的人多 1 元
            indeg[v] -= 1
            if not indeg[v]:  # 所有更低的人都已定薪，v 才能入队定薪
                q.append(v)

    if done < n:  # 还有人没轮到：约束成环，互相矛盾
        print("Poor Xed")
    else:
        print(sum(pay[1:]))


if __name__ == "__main__":
    solve()
