#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 03:13
# update_at: 2026-10-08 03:13

import sys
import heapq

INF = 1 << 62        # 真值上界 Σmax(a) ≤ 1e5·2e9 = 2e14，取它作「不可达」哨兵

type Ints = list[int]              # 一维值序列（原始 a/b、原子段的 A/B、DP 数组都用它）


def atom_segments(a: Ints, b: Ints) -> tuple[Ints, Ints]:
    """按合法切点把序列压成原子段，返回各段的 (A=max a, B=Σb)。

    切点 c（切在 c 与 c+1 之间）合法 ⟺ min_{i≤c} b_i > max_{j>c} a_j；
    这个条件只依赖 c，与划分方案无关，所以合法切点集合唯一确定。
    """
    n = len(a) - 1
    suf = [0] * (n + 2)                     # suf[i] = max a[i..n]（后缀最大值）
    for i in range(n, 0, -1):
        suf[i] = max(suf[i + 1], a[i])

    A, B = [0], [0]                         # 1 下标：第 0 位占位
    mx = sm = 0
    pre = INF                               # 前缀 min b 只需一个游标变量，不必开数组
    for i in range(1, n + 1):
        mx, sm = max(mx, a[i]), sm + b[i]
        pre = min(pre, b[i])
        if i == n or pre > suf[i + 1]:      # i 与 i+1 之间可切 → 这一原子段在此结束
            A.append(mx)
            B.append(sm)
            mx = sm = 0
    return A, B


def feasible(x: int, A: Ints, B: Ints, m: int) -> bool:
    """判定：每块 B 之和 ≤ x 时，Σmax(A) 的最小值是否 ≤ m。

    dp[i] = 前 i 段的最优代价，dp[i] = min_{L-1 ≤ j < i} dp[j] + max(A[j+1..i])，
    L 由 B 的双指针给出。dp 单调不降 + 后缀最大值呈阶梯 → 每个阶梯只取最左端，
    阶梯候选值 = dp[前驱] + A[该阶梯最右元素]，丢进可重集（这里用惰性堆）取最小；
    队首阶梯左端是游标 L-1，单独现算即可。
    """
    s = len(A) - 1
    dp = [INF] * (s + 1)
    dp[0] = 0
    dq = [0] * (s + 2)          # 单调队列（存段下标）：对应 A 值严格递减
    cand = [0] * (s + 2)        # cand[k] = dp[dq[k-1]] + A[dq[k]]，k 非队首时有效
    ver = [0] * (s + 2)         # 槽位 k 被重写的次数：惰性堆靠它识别过期项
    heap = []                   # 可重集等价物：(候选值, 槽位, 版本)
    h = t = 0                   # 队列区间 [h, t)
    L, total = 1, 0
    for i in range(1, s + 1):
        total += B[i]
        while total > x:                    # L = 使 B[L..i] 之和 ≤ x 的最小下标
            total -= B[L]
            L += 1
        while h < t and dq[h] < L:          # 队首阶梯整体滑出窗口
            h += 1
        while h < t and A[dq[t - 1]] <= A[i]:   # 被 A[i] 压住的阶梯永久合并掉
            t -= 1
        if t > h:                           # i 成为最右阶梯，登记它与前驱绑定的候选
            cand[t] = dp[dq[t - 1]] + A[i]
            ver[t] += 1
            heapq.heappush(heap, (cand[t], t, ver[t]))
        dq[t] = i
        t += 1
        best = dp[L - 1] + A[dq[h]]         # 队首阶梯：左端随 L 游走，不进货
        while heap:                             # 惰性删除已出队/被合并的槽位
            slot, stamp = heap[0][1], heap[0][2]   # 堆顶只需槽位号与写入时的版本号
            in_queue = h < slot < t                # 槽位仍在单调队列里
            if in_queue and ver[slot] == stamp:    # 且没被新候选覆写 → 这条记录有效
                break
            heapq.heappop(heap)
        if heap and heap[0][0] < best:
            best = heap[0][0]
        dp[i] = best
    return dp[s] <= m


def best_cut(A: Ints, B: Ints, m: int) -> int:
    """二分最小可行的「每块 B 之和」上界；无解返回 -1（整体一段仍超 m）。"""
    lo, hi = max(B[1:]), sum(B[1:])         # 下界必须 ≥ max B，否则某个原子段自身就超限
    if not feasible(hi, A, B, m):
        return -1
    while lo < hi:
        mid = (lo + hi) // 2
        if feasible(mid, A, B, m):
            hi = mid
        else:
            lo = mid + 1
    return lo


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    a, b = [0] * (n + 1), [0] * (n + 1)
    for i in range(1, n + 1):
        a[i], b[i] = next(data), next(data)

    A, B = atom_segments(a, b)
    print(best_cut(A, B, m))


if __name__ == "__main__":
    solve()
