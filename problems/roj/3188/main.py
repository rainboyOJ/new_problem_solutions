#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 01:10
# update_at: 2026-10-02 01:10

import sys
from bisect import bisect_right
from collections.abc import Callable


def bit_build(size: int) -> list[int]:
    """建容量为 size 的全 1 树状数组：t[i] 管 (i-lowbit(i), i] 这段连续下标。"""
    return [0] + [i & -i for i in range(1, size + 1)]


def bit_add(t: list[int], i: int, delta: int) -> None:
    """单点增减：把下标 i 的可用计数加 delta（下标从 0 起）。"""
    i += 1
    while i < len(t):
        t[i] += delta
        i += i & -i


def bit_sum(t: list[int], i: int) -> int:
    """前缀和：下标 [0, i] 里还剩几支没用的军队（i 为 -1 时得 0）。"""
    s = 0
    i += 1
    while i > 0:
        s += t[i]
        i -= i & -i
    return s


def bit_kth(t: list[int], q: int) -> int:
    """找第 q 个 1 的下标：可用军队按序数出第 q 支，树上倍增下降 O(log n)。"""
    idx, bit = 0, 1 << (len(t).bit_length() - 1)
    while bit:
        nxt = idx + bit
        if nxt < len(t) and t[nxt] < q:   # 这一段整段都不够 q 个，跳过去
            q -= t[nxt]
            idx = nxt
        bit >>= 1
    return idx


def min_time(feasible: Callable[[int], bool], high: int) -> int:
    """可行性随时间单调：在 [0, high] 上二分出最小可行时间。"""
    lo, hi = 0, high
    while lo < hi:
        mid = (lo + hi) // 2
        if feasible(mid):
            hi = mid
        else:
            lo = mid + 1
    return lo


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    adj: list[list[tuple[int, int]]] = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v, w = next(data) - 1, next(data) - 1, next(data)
        adj[u].append((v, w))
        adj[v].append((u, w))
    m = next(data)
    armies = [next(data) - 1 for _ in range(m)]   # 各军队驻扎的城市

    # 从根出发的迭代 DFS：一次拿到父指针、到根距离、子表和先根序
    parent = [-1] * n
    parent[0] = 0             # 根的父亲记成自己，回头时不会被当成孩子
    depth = [0] * n           # 各城市到首都的距离
    pw = [0] * n              # 到父边的权值（根儿子用得上）
    children: list[list[int]] = [[] for _ in range(n)]
    order: list[int] = []
    stack = [0]
    while stack:
        x = stack.pop()
        order.append(x)
        for y, w in adj[x]:
            if y == parent[x]:
                continue
            parent[y] = x
            depth[y] = depth[x] + w
            pw[y] = w
            children[x].append(y)
            stack.append(y)

    # 倍增表：判定时让到不了根的军队 O(log n) 跳到 limit 内最高的祖先
    log = (n - 1).bit_length()                  # 2^log ≥ 最长链
    up = [[0] * n for _ in range(log)]
    up[0] = parent[:]                            # 根指向自己，跳不出去
    for k in range(1, log):
        prev, row = up[k - 1], up[k]
        for x in range(n):
            row[x] = prev[prev[x]]

    # 每支军队属于哪个根儿子的子树（根的儿子上不算，-1 表示没有"自己的子树"）
    origin = [-1] * n
    for x in order[1:]:
        origin[x] = x if parent[x] == 0 else origin[parent[x]]

    tops = sorted(children[0], key=lambda c: -pw[c])   # 需求按边权从大到小
    tid = {c: i for i, c in enumerate(tops)}
    armies.sort(key=lambda s: depth[s])          # 按到根距离升序
    d_sorted = [depth[s] for s in armies]
    groups: list[list[int]] = [[] for _ in tops]     # 每个根儿子有哪些军队
    for idx, s in enumerate(armies):
        c = origin[s]
        if c != -1:
            groups[tid[c]].append(idx)
    gd = [[depth[armies[i]] for i in g] for g in groups]   # 组内同样升序

    cp = [0] * n          # 本轮检查点标记
    cov = [0] * n         # 根到此点是否已有检查点
    unc = [0] * n         # 子树里是否还有没被覆盖的叶子

    def feasible(limit: int) -> bool:
        """limit 小时内能否让每条「首都→边境」路径上都有检查点。"""
        f = bisect_right(d_sorted, limit)        # 能走到首都的军队数
        marks: list[int] = []
        for idx in range(f, m):                  # 走不到首都的：原地走到最高可达祖先
            s = armies[idx]
            th = depth[s] - limit                # 祖先距离下限，恒大于 0，跳不进根
            x = s
            for k in range(log - 1, -1, -1):
                y = up[k][x]
                if depth[y] >= th:
                    x = y
            cp[x] = 1
            marks.append(x)

        cov[0] = cp[0]
        for x in order[1:]:                      # 检查点沿先根序向下渗透
            cov[x] = cp[x] or cov[parent[x]]
        for x in reversed(order):                # 自底向上找「还有裸叶子」的子树
            if cov[x]:
                unc[x] = 0
            elif children[x]:
                unc[x] = 0
                for ch in children[x]:
                    if unc[ch]:
                        unc[x] = 1
                        break
            else:
                unc[x] = 1                       # 叶子且从根到此无检查点
        needs: list[int] = []
        for c in tops:
            if unc[c]:
                needs.append(c)
                if len(needs) > f:               # 需求比预备队还多，直接判负
                    break

        ok = len(needs) <= f
        if ok:
            t = bit_build(f)                     # 只给能到根的军队编号 [0, f)
            used = bytearray(m)
            curs = [-2] * len(tops)              # -2 = 该组还没算过可动上界
            for c in needs:
                g, gtid = groups[tid[c]], tid[c]
                if g:                            # 优先用"自己子树"的军队免费落在 c
                    cur = curs[gtid]
                    if cur == -2:
                        cur = bisect_right(gd[gtid], limit) - 1
                    while cur >= 0 and used[g[cur]]:
                        cur -= 1
                    curs[gtid] = cur
                    if cur >= 0:
                        idx = g[cur]
                        used[idx] = 1
                        bit_add(t, idx, -1)
                        continue
                # 否则从首都折返下到 c：耗时 depth+w ≤ limit，即挑剩余时间够的最弱一支
                pos = bisect_right(d_sorted, limit - pw[c]) - 1
                q = bit_sum(t, pos)
                if q == 0:
                    ok = False
                    break
                idx = bit_kth(t, q)
                used[idx] = 1
                bit_add(t, idx, -1)

        for x in marks:                          # 清掉本轮检查点，供下次判定复用
            cp[x] = 0
        return ok

    # 每支军队最多盖住一个根儿子子树，m 支盖不齐 k 个子树时无解
    if len(tops) > m:
        print(-1)
        return
    high = max(depth) + max(pw[c] for c in tops)   # 此时全员预备队、剩余时间都够
    print(min_time(feasible, high))


if __name__ == "__main__":
    solve()
