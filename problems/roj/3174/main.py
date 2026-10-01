#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def min_soldiers(children: list[list[int]], root: int) -> int:
    """树形 DP：返回覆盖所有边的最少士兵数（即树的最小点覆盖）。"""
    order = [root]
    for u in order:          # 队列在遍历中增长，得到从根出发的 BFS 序
        order += children[u]

    # dp0[u]：u 不放士兵时子树的最小代价，此时每条 (u,c) 只能靠 c 覆盖
    # dp1[u]：u 放士兵时子树的最小代价，先记上自己这 1 个
    dp0 = [0] * len(order)
    dp1 = [1] * len(order)

    for u in reversed(order):  # 逆 BFS 序保证算 u 时所有儿子已算完
        for c in children[u]:
            dp0[u] += dp1[c]
            dp1[u] += min(dp0[c], dp1[c])

    return min(dp0[root], dp1[root])


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    while (n_tok := next(data, None)) is not None:  # 多组数据，读到 EOF 为止
        n = int(n_tok)
        children: list[list[int]] = [[] for _ in range(n)]
        root = -1
        for _ in range(n):  # 每行：节点编号:(子节点数) 子节点…，首 token 形如 0:(2)
            head = next(data)  # bytes
            u, cnt = map(int, head[:-1].split(b':('))
            root = u if root < 0 else root  # 第一行描述的就是树根
            children[u] = [int(next(data)) for _ in range(cnt)]
        out.append(str(min_soldiers(children, root)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
