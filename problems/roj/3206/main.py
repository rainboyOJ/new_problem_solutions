#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 01:44
# update_at: 2026-10-02 02:12

import sys


def reachable_sets(adj: list[list[int]], n: int) -> list[list[int]]:
    """每个点沿有向边能到达的点集（不含自己），即把图预传递成闭包。"""
    reach: list[list[int]] = [[] for _ in range(n + 1)]
    for src in range(1, n + 1):
        seen = [False] * (n + 1)
        queue = adj[src][:]
        for v in queue:
            seen[v] = True        # 先整层标记，避免多边把同一个点重复入队
        head = 0
        while head < len(queue):
            u = queue[head]
            head += 1
            for v in adj[u]:
                if not seen[v]:
                    seen[v] = True
                    queue.append(v)
        reach[src] = queue
    return reach


def max_matching(reach: list[list[int]], n: int) -> int:
    """二分图最大匹配（匈牙利）。左部点 x 连向右部点 y，当且仅当 x 能到达 y。

    用迭代版 DFS 代替递归：栈帧是 [左部点, 下一个待试邻居下标, 选中的右部点]，
    找到空闲右部点时整条交替路一起换匹配边，就完成一次增广。
    每个左部点只需搜一次：处理完前 i 个左部点后，当前匹配已是它们诱导子图上的最大匹配。
    """
    match_l = [0] * (n + 1)   # 左部点 x 配到的右部点，0 表示未配对
    match_r = [0] * (n + 1)   # 右部点 y 配到的左部点，0 表示空闲
    pairs = 0
    for root in range(1, n + 1):
        if match_l[root]:
            continue
        used = [False] * (n + 1)   # 本次搜索走过的右部点，防止来回绕圈
        stack = [[root, 0, 0]]
        while stack:
            frame = stack[-1]
            nbr = reach[frame[0]]
            i = frame[1]
            while i < len(nbr) and used[nbr[i]]:
                i += 1
            frame[1] = i + 1
            if i == len(nbr):          # 该左部点没有别的出路，回溯上一层
                stack.pop()
                continue
            v = nbr[i]
            used[v] = True
            frame[2] = v
            if match_r[v] == 0:        # 右部点空闲，增广路打通
                break
            stack.append([match_r[v], 0, 0])   # 让 v 的原配点另寻出路
        if stack:                      # 栈非空说明增广成功，栈里就是从 root 出发的交替路
            for u, _i, v in stack:     # 交替路上每条边换成匹配边
                match_l[u] = v
                match_r[v] = u
            pairs += 1
    return pairs


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        x, y = next(data), next(data)
        adj[x].append(y)

    reach = reachable_sets(adj, n)
    # 最小路径点覆盖 = n - 最大匹配；答案正是这个最小值
    print(n - max_matching(reach, n))


if __name__ == "__main__":
    solve()
