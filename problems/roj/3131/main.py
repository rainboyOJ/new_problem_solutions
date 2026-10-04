#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 19:14
# update_at: 2026-10-01 19:45

import sys

import numpy as np

NIE = "NIE"  # 到第 K 场雨结束仍然凑不够的国家输出它
CAP = 2 * 10**9  # 单个太空站的收集量上限：已经远超任何国家的需求 10^9，再大也不会改变判定


def collect(
    lo: np.ndarray,
    hi: np.ndarray,
    own: np.ndarray,
    l: np.ndarray,
    r: np.ndarray,
    a: np.ndarray,
    k: int,
    m: int,
) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
    """一轮整体二分：算出每个活跃国家在左边那半场雨里能收到多少样本量。

    活跃国家当前的答案区间 [lo, hi] 就是一个"节点"。同一轮里所有国家的区间深度相同，
    所以这些区间把 [1, k+1] 切成互不相交的几段，一场雨只属于唯一节点，可以一起算。
    返回 (act, mid, S)：act 是活跃国家下标，mid 是各自节点的二分中点，S 是收集量。
    """
    act = np.nonzero(lo < hi)[0]
    # 节点用 lo*(k+2)+hi 编码；unique 后按 lo 升序，正好可以二分定位一场雨属于哪个节点
    uniq, inv = np.unique(lo[act] * (k + 2) + hi[act], return_inverse=True)
    node_lo, node_hi = uniq // (k + 2), uniq % (k + 2)
    node_mid = (node_lo + node_hi) >> 1
    mid = node_mid[inv]

    op = np.arange(1, k + 1)  # 雨的编号，1 基
    node_of = np.searchsorted(node_lo, op, side="right") - 1  # 每场雨落在哪个节点
    # 已经定完答案的国家会让区间出现空洞，落在空洞里的雨不属于任何节点（node_of = -1）
    keep = (node_of >= 0) & (op <= node_mid[node_of])  # 只保留每条二分路径的左半边
    op, node_of = op[keep], node_of[keep]
    left, right, val = l[op - 1], r[op - 1], a[op - 1]
    wrap = left > right  # 环形区间跨过 m，拆成 [left, m] 和 [1, right]

    # 区间加 → 差分：left 处 +val；跨环时在 1 处再 +val；right 之后 -val
    tail = right < m
    ev_node = np.concatenate([node_of, node_of[wrap], node_of[tail]])
    ev_pos = np.concatenate([left, np.ones(int(wrap.sum()), np.int64), right[tail] + 1])
    ev_del = np.concatenate([val, val[wrap], -val[tail]])

    key = ev_node * (m + 1) + ev_pos  # 同节点内按位置升序
    order = np.argsort(key, kind="stable")
    ev_node, ev_key, ev_del = ev_node[order], key[order], ev_del[order]
    cum = np.cumsum(ev_del)
    # 累加要按节点清零：减去"该节点块首之前"的累计，就是节点内的前缀和
    head = np.searchsorted(ev_node, ev_node, side="left")
    cum_in = cum - (cum[head] - ev_del[head])

    # 只问活跃国家的太空站落在哪
    live = np.zeros(lo.size, bool)
    live[act] = True
    own0 = own - 1
    station = live[own0]
    qpos = np.nonzero(station)[0] + 1
    qcid = own0[station]
    node_of_country = np.zeros(lo.size, np.int64)
    node_of_country[act] = inv
    qnode = node_of_country[qcid]

    qkey = qnode * (m + 1) + qpos
    j = np.searchsorted(ev_key, qkey, side="right") - 1  # 节点内最后一个不晚于该位置的事件
    hit = j >= 0  # 前面没有任何事件时不能取 cum_in[0] 硬凑
    j = np.where(hit, j, 0)
    found = hit & (ev_node[j] == qnode)  # 该事件确实属于本节点
    got = np.where(found, cum_in[j], 0)
    # 一个国家最多有 m 个太空站，逐个累加会到 10^19 撑爆 int64；先按 CAP 截断，
    # 由于任何国家的需求都不超过 10^9 < CAP，截断不会改变 "S >= res" 的结论。
    got = np.minimum(got, CAP)
    # 同一国家有多个太空站：按国家求和（总量 ≤ 3×10^5 * 2×10^9 < 2^53，float64 精确）
    total = np.bincount(qcid, weights=got.astype(np.float64), minlength=lo.size)
    return act, mid, total[act].astype(np.int64)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)                         # 国家数
    m = next(data)                         # 轨道段数
    own = np.array([next(data) for _ in range(m)], dtype=np.int64)      # 第 i 段轨道属于哪个国家
    need = np.array([next(data) for _ in range(n)], dtype=np.int64)     # 第 i 个国家想收集的样本量
    k = next(data)                         # 雨的场数
    rain = np.array([[next(data), next(data), next(data)] for _ in range(k)], dtype=np.int64)  # 每场雨 (L, R, A)
    left, right, amount = rain[:, 0], rain[:, 1], rain[:, 2]

    lo = np.ones(n, np.int64)              # 答案区间 [lo, hi]
    hi = np.full(n, k + 1, np.int64)       # hi = k+1 表示到 K 场雨结束仍不够
    res = need.copy()                      # 还没被满足的需求，雨量按二分逐段扣
    act = np.nonzero(lo < hi)[0]
    while act.size:
        act, mid, S = collect(lo, hi, own, left, right, amount, k, m)
        ok = S >= res[act]                 # 够：答案在左半边；不够：扣掉雨量去右半边
        hi[act[ok]] = mid[ok]
        res[act[~ok]] -= S[~ok]
        lo[act[~ok]] = mid[~ok] + 1
        act = np.nonzero(lo < hi)[0]

    print("\n".join(NIE if v == k + 1 else str(int(v)) for v in lo))


if __name__ == "__main__":
    solve()
