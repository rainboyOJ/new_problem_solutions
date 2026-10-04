#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 20:42
# update_at: 2026-10-01 20:42

import sys
from array import array

NEG = -10**9  # 「不可行」哨兵：比任何合法权值和都小一个数量级


def rect_max(a: list[int], kind: int) -> list[int]:
    """对上一层 (p, q) 权值表做区域最大值查询，结果表下标 [l][r] 即当前行取 [l, r] 的最优前驱值。

    四种 kind 对应四种单调转移允许的前驱区域（p=上一行左端点, q=上一行右端点）：
    kind 0：方形 p, q ∈ [l, r]（两端点都还在「先减/先增」段）；
    kind 1：p ≤ l 且 q ∈ [l, r]（左端点已过谷, 右端点仍在递增段）；
    kind 2：p ∈ [l, r] 且 q ≥ r（左端点仍在递减段, 右端点已过峰）；
    kind 3：p ≤ l 且 q ≥ r（两端点都已拐弯, 持续收缩）。
    """
    m = int(len(a) ** 0.5)
    if kind == 3:  # 两次单向扫描：行内右后缀 max（q ≥ r）+ 列向前缀 max（p ≤ l）
        res = a[:]
        for p in range(m):
            b, t = p * m, NEG
            for q in range(m - 1, -1, -1):  # 行内从右往左并
                if res[b + q] > t:
                    t = res[b + q]
                res[b + q] = t
        for p in range(1, m):
            for q in range(m):
                u = res[(p - 1) * m + q]
                if u > res[p * m + q]:
                    res[p * m + q] = u
        return res
    if kind == 1:  # 先列向并（p ≤ l），再行内从 q=l 起右扫（q ∈ [l, r]）
        e = a[:]
        for p in range(1, m):
            for q in range(m):
                u = e[(p - 1) * m + q]
                if u > e[p * m + q]:
                    e[p * m + q] = u
        res = [NEG] * (m * m)
        for l in range(m):
            b, t = l * m, NEG
            for q in range(l, m):
                if e[b + q] > t:
                    t = e[b + q]
                res[b + q] = t
        return res
    if kind == 2:  # 先行内右后缀（q ≥ r），再列内从 p=r 往上扫（p ∈ [l, r]）
        g = a[:]
        for p in range(m):
            b, t = p * m, NEG
            for q in range(m - 1, -1, -1):
                if g[b + q] > t:
                    t = g[b + q]
                g[b + q] = t
        res = [NEG] * (m * m)
        for r in range(m):
            t = NEG
            for p in range(r, -1, -1):
                if g[p * m + r] > t:
                    t = g[p * m + r]
                res[p * m + r] = t
        return res
    # kind 0：方形 [l, r]×[l, r]。行 max + 列 max 后按边长递推：
    # 方形 [l, r] = 方形 [l+1, r] ∪ 第 l 行 ∪ 第 l 列
    rp = a[:]
    for p in range(m):
        b = p * m
        for q in range(1, m):
            u = rp[b + q - 1]
            if u > rp[b + q]:
                rp[b + q] = u
    cp = [NEG] * (m * m)  # 列向只从 p=l 起并：p<l 的槽是合法状态，不能混进方形
    for l in range(m):
        t = NEG
        for p in range(l, m):
            x = a[p * m + l]
            if x > t:
                t = x
            cp[p * m + l] = t
    res = [NEG] * (m * m)
    for d in range(m):  # d = r - l，小边长先算
        for l in range(m - d):
            r = l + d
            v = rp[l * m + r]  # 第 l 行 q ∈ [l, r]（q<l 的槽 p>q 恒为哨兵）
            c = cp[r * m + l]  # 第 l 列 p ∈ [l, r]
            if c > v:
                v = c
            if d:
                u = res[(l + 1) * m + r]
                if u > v:
                    v = u
            res[l * m + r] = v
    return res


# (目标状态层, 可用的上一层状态层, rect_max 的区域种类)
# 状态层 s = fl*2+fr：fl=1 表示左端点已过谷（开始递增），fr=1 表示右端点已过峰（开始递减）
COMBOS = (
    (0, (0,), 0),               # (0,0) ← (0,0)        两端都未拐弯
    (2, (0, 2), 1),             # (1,0) ← (0,0)/(1,0)  左过谷、右仍递增
    (1, (0, 1), 2),             # (0,1) ← (0,0)/(0,1)  左仍递减、右过峰
    (3, (0, 1, 2, 3), 3),       # (1,1) ← 任意         两端都已拐弯，持续收缩
)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, k = next(data), next(data), next(data)
    w = [[next(data) for _ in range(m)] for _ in range(n)]

    if k == 0:  # 空连通块
        print("Oil : 0")
        return

    pre = [[0] * (m + 1) for _ in range(n)]  # 行前缀和：区间 [l, r] 和 = pre[i][r+1] - pre[i][l]
    for i in range(n):
        for c, x in enumerate(w[i]):
            pre[i][c + 1] = pre[i][c] + x

    segs = [(l, r) for l in range(m) for r in range(l, m)]  # 合法列区间，扁平槽位 W = l*m + r
    slots = [l * m + r for l, r in segs]
    sizes = [r - l + 1 for l, r in segs]
    m2, k1 = m * m, k + 1

    # 四层 DP 表，下标 [s][j*m2 + W]：已用 j 格、当前行取该区间、单调状态 s 的最大权值和
    F = [[NEG] * (k1 * m2) for _ in range(4)]
    hist: list[tuple] = []  # 每行结束后冻结一张表，供最后回溯方案
    best, best_state = NEG, (0, 0, 0)

    for i in range(n):
        newF = [[NEG] * (k1 * m2) for _ in range(4)]
        seg_row = [pre[i][r + 1] - pre[i][l] for l, r in segs]  # 本行每个区间的权值和
        jtop = min(k - 1, i * m)  # 上一层最多 i*m 格；且 j + size ≤ k ⇒ j ≤ k-1
        for dst_s, srcs, kind in COMBOS:
            dst = newF[dst_s]
            for jp in range(1, jtop + 1):
                base = jp * m2
                A = F[srcs[0]][base:base + m2]  # 可用源层逐槽取 max 合成一张表
                for s in srcs[1:]:
                    B = F[s]
                    for t in range(m2):
                        x = B[base + t]
                        if x > A[t]:
                            A[t] = x
                if max(A) <= NEG // 2:  # 该层源状态全不可达
                    continue
                R = rect_max(A, kind)
                for t, W in enumerate(slots):
                    jn = jp + sizes[t]
                    if jn > k:
                        continue
                    v = R[W] + seg_row[t]
                    if v <= NEG // 2:
                        continue
                    slot = jn * m2 + W
                    if v > dst[slot]:
                        dst[slot] = v
        # 本行作为连通块首行：单调状态回到 (0,0)，之前各行均为 0 格
        for t, W in enumerate(slots):
            if sizes[t] <= k:
                slot = sizes[t] * m2 + W
                if seg_row[t] > newF[0][slot]:
                    newF[0][slot] = seg_row[t]
        # 连通块可以在任意一行结束：记录「恰 k 格」的历史最优
        base_k = k * m2
        for s in range(4):
            layer = newF[s]
            for W in slots:
                v = layer[base_k + W]
                if v > best:
                    best, best_state = v, (i, s, W)
        hist.append(tuple(array("i", layer) for layer in newF))
        F = newF

    # 回溯：从最优终点逐行往回找一个取到该值的前驱，找不到即说明本行是首行
    end_row, s, W = best_state
    l, r = divmod(W, m)
    j = k
    picked: list[tuple[int, int, int]] = []
    while True:
        picked.append((end_row, l, r))
        size = r - l + 1
        jp = j - size
        fl, fr = s >> 1, s & 1
        want = hist[end_row][s][j * m2 + W] - (pre[end_row][r + 1] - pre[end_row][l])
        nxt = None
        if end_row > 0:
            prev = hist[end_row - 1]
            for s0 in range(4):
                if (s0 >> 1) > fl or (s0 & 1) > fr:  # 拐过的弯不能回退
                    continue
                for p in range(m - 1, -1, -1):  # 多个等优前驱时从大到小扫描
                    if (fl == 0 and p < l) or (fl == 1 and p > l):  # 左端点单调方向
                        continue
                    for q in range(m - 1, -1, -1):
                        if (fr == 0 and q > r) or (fr == 1 and q < r):  # 右端点单调方向
                            continue
                        if q < l or p > r or p > q:  # 相邻行相交（连通）且前驱区间合法
                            continue
                        if prev[s0][jp * m2 + p * m + q] == want:
                            nxt = (s0, p, q)
                            break
                    if nxt:
                        break
        if nxt is None:  # 没有前驱行：本行即连通块首行
            break
        s, l, r = nxt
        W = l * m + r
        j, end_row = jp, end_row - 1

    picked.reverse()  # 输出按行号、列号升序
    out = [f"Oil : {best}"]
    out += [f"{ri + 1} {c + 1}" for ri, l, r in picked for c in range(l, r + 1)]
    print("\n".join(out))


if __name__ == "__main__":
    solve()
