#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 18:01
# update_at: 2026-09-30 18:01

import sys
from collections import defaultdict


def assign_times(root: int, graph: dict[int, list[int]]) -> tuple[dict[int, int], dict[int, int]]:
    """迭代 DFS 给有根树标括号序：tin[u] 是 u 的进入时刻，tout[u] 是 u 子树中最后的进入时刻。

    栈元素是 (节点, 父节点, 阶段)：父节点 None 表示没有（根）；阶段 0 进入，记时刻后把
    同一节点的离开阶段压回，再压孩子；阶段 1 离开，只收尾。时刻只在进入时递增，且离开时
    孩子必然已全部进入，所以 tout[u] 恰等于 u 子树中的最大 tin——子树被压进一个连续区间。
    """
    tin: dict[int, int] = {}
    tout: dict[int, int] = {}
    timer = 0
    stack: list[tuple[int, int | None, int]] = [(root, None, 0)]
    while stack:
        u, parent, stage = stack.pop()
        if stage == 0:
            timer += 1
            tin[u] = timer
            stack.append((u, parent, 1))                          # 排队等待本子树走完后收尾
            stack += [(v, u, 0) for v in graph[u] if v != parent]  # 父亲不回头
        else:
            tout[u] = timer
    return tin, tout


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    graph: dict[int, list[int]] = defaultdict(list)
    root = -1  # 输入保证会遇到 b = -1 的那一行，把根记在这里
    for _ in range(n):
        a, b = next(data), next(data)
        if b == -1:
            root = a
        else:
            graph[a].append(b)
            graph[b].append(a)

    tin, tout = assign_times(root, graph)

    m = next(data)
    out: list[str] = []
    for _ in range(m):
        x, y = next(data), next(data)
        # 祖先的 [tin, tout] 区间完整盖住后代的进入时刻；x ≠ y 时两者不会同时成立
        x_is_ancestor = tin[x] <= tin[y] <= tout[x]
        y_is_ancestor = tin[y] <= tin[x] <= tout[y]
        out.append('1' if x_is_ancestor else '2' if y_is_ancestor else '0')

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
