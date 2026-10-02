#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:01
# update_at: 2026-10-02 08:50

import sys
from array import array

INF = 10**9  # 空后缀的哨兵：比 1..n 里任何值都大


def build_conflicts(a: list[int], n: int) -> tuple[list[int], array]:
    """建「不能进同一个栈」的冲突图，返回 CSR 邻接表 (start, edges)。

    存在 i<j<k 使 a[k]<a[i]<a[j] 时，a[i] 与 a[j] 连边：同栈里 a[j] 压在
    a[i] 上必须先弹，但更小的 a[k] 又排在它俩之前要先输出，a[i] 只能晚于
    a[j] 弹出，与升序输出矛盾，所以这两个值必须分进两个栈。
    最坏约 n²/2 条边，用「度数前缀和 + 回填」的 CSR 存储，内存只有 O(n+E)。
    """
    suf = [INF] * (n + 2)  # suf[j] = min(a[j..n])（下标 1..n，n+1 位是空后缀哨兵
    for i in range(n, 0, -1):
        suf[i] = min(a[i - 1], suf[i + 1])

    deg = [0] * (n + 1)  # 第一遍：数出每个值连了多少条边
    for j in range(1, n + 1):
        m = suf[j + 1]  # 位置 j 之后的最小值，即候选的 a[k]
        for i in range(1, j):
            x = a[i - 1]
            if m < x < a[j - 1]:  # a[k] < a[i] < a[j]
                deg[x] += 1
                deg[a[j - 1]] += 1

    start = [0] * (n + 2)  # 前缀和：值 u 的邻接边存放在 [start[u], start[u+1])
    for u in range(1, n + 1):
        start[u + 1] = start[u] + deg[u]

    edges = array("I", bytes(4 * start[n + 1]))
    fill = start[:]  # 第二遍：沿各自的游标回填，复用前缀和数组当游标
    for j in range(1, n + 1):
        m = suf[j + 1]
        for i in range(1, j):
            x = a[i - 1]
            if m < x < a[j - 1]:
                edges[fill[x]] = a[j - 1]
                fill[x] += 1
                edges[fill[a[j - 1]]] = x
                fill[a[j - 1]] += 1
    return start, edges


def two_color(start: list[int], edges: array, n: int, first: dict[int, int]) -> list[int]:
    """给每个值染 0/1（0 = 进 S1，1 = 进 S2）；相邻必须异色，染不上返回空列表。

    二分图每个连通块的染色整体可翻转：把「输入位置最早」的成员翻成 0，
    贪心压入时就能先出字典序更小的 a；同块其余值跟着整体翻转。
    """
    color = [-1] * (n + 1)
    for seed in range(1, n + 1):
        if color[seed] != -1:
            continue
        color[seed] = 0
        queue = [seed]
        for u in queue:  # 列表边出队边追加，块内成员都收在 queue 里
            for t in range(start[u], start[u + 1]):
                v = edges[t]
                if color[v] == -1:
                    color[v] = color[u] ^ 1
                    queue.append(v)
                elif color[v] == color[u]:
                    return []  # 奇环：两个栈怎么分工都不够用
        anchor = min(queue, key=first.__getitem__)  # 输入位置最早的成员
        if color[anchor]:  # 整块翻转，让 anchor 染 0
            for u in queue:
                color[u] ^= 1
    return color


def smallest_ops(a: list[int], n: int, color: list[int]) -> str | None:
    """贪心产出字典序最小的操作序列；凑不出 1..n 则返回 None。

    四个操作按字典序是 a<b<c<d，每一步在「当前合法的操作」里挑最小的：
    - 压入的值必须比栈顶小：把大的盖在小的上面，小的是将来的 need，
      永远轮不到弹出，这种压法一定死路，不合法；
    - 合法时先压 a——它比 b、d 都小，且「先压后弹」与「先弹后压」
      到达完全相同的状态，晚一步弹 d 不会变差；
    - 否则能弹出 need 的 b 最小（能弹 b 时压 a 必然非法），再轮到合法的 c，
      最后才是 d——b 与先压 c 再弹同样等价，c 与先弹 d 后压同样等价；
    - 输入耗尽只能弹，弹不出 need 说明这个染色救不回来。
    """
    s1: list[int] = []
    s2: list[int] = []
    ops: list[str] = []
    ptr = 0  # 下一个待压入的输入下标
    need = 1  # 下一个该输出的值
    while need <= n:
        b_now = bool(s1) and s1[-1] == need  # 此刻能否弹 b
        d_now = bool(s2) and s2[-1] == need  # 此刻能否弹 d
        if ptr == n:  # 输入耗尽，只能弹
            if b_now:
                s1.pop()
                ops.append("b")
            elif d_now:
                s2.pop()
                ops.append("d")
            else:
                return None  # 弹不出 need：这个染色方案救不回来
            need += 1
            continue

        v = a[ptr]
        push_s1 = color[v] == 0 and (not s1 or v < s1[-1])  # 染给 S1 且压入合法
        push_s2 = color[v] == 1 and (not s2 or v < s2[-1])  # 染给 S2 且压入合法
        if push_s1:  # a 最小，合法就先压
            s1.append(v)
            ops.append("a")
            ptr += 1
        elif b_now:  # 压 a 非法时 b 最小
            s1.pop()
            ops.append("b")
            need += 1
        elif push_s2:  # c 比 d 小
            s2.append(v)
            ops.append("c")
            ptr += 1
        elif d_now:  # 压 c 非法（会盖死 need），只剩 d
            s2.pop()
            ops.append("d")
            need += 1
        else:
            return None  # 无路可走：这个染色方案救不回来
    return " ".join(ops)


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    a = data[1 : n + 1]
    if len(a) < n:  # 输入不足 n 个值，构不成 1..n 的排列
        print(0)
        return
    first = {v: i for i, v in enumerate(a)}  # 每个值在输入里的位置
    start, edges = build_conflicts(a, n)
    color = two_color(start, edges, n, first)
    ans = smallest_ops(a, n, color) if color else None
    print(ans if ans else 0)


if __name__ == "__main__":
    solve()
