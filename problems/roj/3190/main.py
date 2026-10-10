#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 13:48
# update_at: 2026-10-09 13:48
#
# ROJ 3190《天天爱跑步》(NOIP2016 提高组)：树上差分 + 倍增 LCA。
# 玩家路径 S->T 在 L = LCA(S,T) 处拆成上行段 S->L 与下行段 L->T：
#   上行段命中条件 depth[u] + W[u] == depth[S]
#   下行段命中条件 depth[u] - W[u] == 2 * depth[L] - depth[S]
# 每条路径只产生两个桶上的差分事件，后序遍历进出子树时用全局桶取差值。

import sys

LOG = 19         # 倍增层数：2^19 > 3 * 10^5
OFFSET = 300005  # 下行段桶的偏移，depth[u] - W[u] 可能为负

type Adj = list[list[int]]   # 下标为节点编号，值为邻接点或该节点上的事件值
type Jump = list[list[int]]  # up[u][i] = 节点 u 的 2^i 级祖先，越界为 0


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n = next(data)
        m = next(data)
    except StopIteration:  # 空输入保护
        return

    adj: Adj = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u = next(data)
        v = next(data)
        adj[u].append(v)
        adj[v].append(u)

    W = [0] * (n + 1)  # W[u]：节点 u 的观察时刻
    for i in range(1, n + 1):
        W[i] = next(data)

    # 以 1 为根 BFS，顺便求出深度、倍增表与 BFS 序（链状树也不会爆栈）
    up: Jump = [[0] * LOG for _ in range(n + 1)]
    depth = [0] * (n + 1)
    q = [1]
    depth[1] = 1
    head = 0
    while head < len(q):
        u = q[head]
        head += 1
        for i in range(1, LOG):
            up[u][i] = up[up[u][i - 1]][i - 1]
        for v in adj[u]:
            if v != up[u][0]:
                depth[v] = depth[u] + 1
                up[v][0] = u
                q.append(v)

    def get_lca(u: int, v: int) -> int:
        """倍增求 u、v 的最近公共祖先。"""
        if depth[u] < depth[v]:
            u, v = v, u
        diff = depth[u] - depth[v]
        for i in range(LOG - 1, -1, -1):
            if (diff >> i) & 1:
                u = up[u][i]
        if u == v:
            return u
        for i in range(LOG - 1, -1, -1):
            if up[u][i] != up[v][i]:
                u = up[u][i]
                v = up[v][i]
        return up[u][0]

    # 上行段事件值 = depth[S]，下行段事件值 = 2 * depth[L] - depth[S]
    ev_add1: Adj = [[] for _ in range(n + 1)]  # 在 S 入桶
    ev_del1: Adj = [[] for _ in range(n + 1)]  # 在 L 的父节点出桶
    ev_add2: Adj = [[] for _ in range(n + 1)]  # 在 T 入桶
    ev_del2: Adj = [[] for _ in range(n + 1)]  # 在 L 出桶，L 只由上行段统计

    for _ in range(m):
        s = next(data)
        t = next(data)
        lca = get_lca(s, t)
        val1 = depth[s]
        ev_add1[s].append(val1)
        if up[lca][0] != 0:
            ev_del1[up[lca][0]].append(val1)
        val2 = 2 * depth[lca] - depth[s]
        ev_add2[t].append(val2)
        ev_del2[lca].append(val2)

    cnt1 = [0] * (2 * OFFSET)  # cnt1[v]：值 depth[S] = v 仍生效的上行段条数
    cnt2 = [0] * (3 * OFFSET)  # cnt2[v + OFFSET]：值 2 * depth[L] - depth[S] = v 的下行段条数

    ans = [0] * (n + 1)
    pre_val1 = [0] * (n + 1)   # pre_val1[u]：进入 u 前 cnt1[depth[u] + W[u]] 的值
    pre_val2 = [0] * (n + 1)   # pre_val2[u]：进入 u 前 cnt2[depth[u] - W[u] + OFFSET] 的值

    # 手工栈做后序遍历：state 0 = 刚进入（先记桶的旧值），state 1 = 子树已处理完
    stack = [1]
    state = [0]
    while stack:
        u = stack.pop()
        st = state.pop()

        if st == 0:
            stack.append(u)
            state.append(1)
            req1 = depth[u] + W[u]
            if 0 <= req1 < len(cnt1):
                pre_val1[u] = cnt1[req1]
            req2 = depth[u] - W[u] + OFFSET
            if 0 <= req2 < len(cnt2):
                pre_val2[u] = cnt2[req2]
            for v in adj[u]:
                if v != up[u][0]:
                    stack.append(v)
                    state.append(0)
        else:
            for val1 in ev_add1[u]:
                cnt1[val1] += 1
            for val1 in ev_del1[u]:
                cnt1[val1] -= 1
            for val2 in ev_add2[u]:
                cnt2[val2 + OFFSET] += 1
            for val2 in ev_del2[u]:
                cnt2[val2 + OFFSET] -= 1

            req1 = depth[u] + W[u]
            if 0 <= req1 < len(cnt1):
                ans[u] += cnt1[req1] - pre_val1[u]
            req2 = depth[u] - W[u] + OFFSET
            if 0 <= req2 < len(cnt2):
                ans[u] += cnt2[req2] - pre_val2[u]

    print(' '.join(map(str, ans[1:])))


if __name__ == '__main__':
    solve()
