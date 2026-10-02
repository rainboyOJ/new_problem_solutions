#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:08
# update_at: 2026-10-02 10:08

import sys
from fractions import Fraction
from math import inf

INF = 10**18  # 倍增表里"这一轮走不完"的哨兵代价，恒大于预算上限 10^9


def prefix(bit: list[int], p: int) -> int:
    """树状数组前缀和：已标记（东部）城市里排名落在前 p 名的数量。"""
    total = 0
    while p:
        total += bit[p]
        p -= p & -p
    return total


def mark(bit: list[int], p: int) -> None:
    """把排名 p 的城市计入树状数组——它此后就是更小编号城市的"东部城市"。"""
    n = len(bit) - 1
    while p <= n:
        bit[p] += 1
        p += p & -p


def kth(bit: list[int], k: int) -> int:
    """第 k 小已标记排名所在的位置（树状数组二进制提升，O(log n)）。"""
    n = len(bit) - 1
    pos = 0
    step = 1 << (n.bit_length() - 1)
    while step:
        nxt = pos + step
        if nxt <= n and bit[nxt] < k:
            k -= bit[nxt]
            pos = nxt
        step >>= 1
    return pos + 1


def nearest_two(h: list[int]) -> tuple[list[int], list[int]]:
    """每个城市的最近、次近东部城市（0 表示不存在）。

    距离即海拔差绝对值，同距视为海拔低者更近。按海拔升序、从大编号往小编号处理，
    已标记的恰是东部城市；候选只需已标记排名中紧邻它的至多四个（低侧两个、高侧两个），
    更外侧的东部城市距离严格更大，进不了前二。
    """
    n = len(h) - 1
    order = sorted(range(1, n + 1), key=h.__getitem__)  # 海拔升序的城市编号
    rank = [0] * (n + 1)
    for r, city in enumerate(order, 1):
        rank[city] = r  # 树状数组用 1-based 排名
    bit = [0] * (n + 1)
    near = [0] * (n + 1)
    second = [0] * (n + 1)
    for city in range(n, 0, -1):
        r = rank[city]
        less = prefix(bit, r - 1)  # 海拔比它低的东部城市个数
        east = n - city            # 东部城市总数（恰有 n-city 个已标记）
        # 低侧第 less、less-1 名，高侧第 less+1、less+2 名
        cands = [order[kth(bit, k) - 1] for k in (less, less - 1, less + 1, less + 2) if 1 <= k <= east]
        cands.sort(key=lambda c: (abs(h[city] - h[c]), h[c]))  # 距离相同视为海拔低者更近
        if cands:
            near[city] = cands[0]
            second[city] = cands[1] if len(cands) > 1 else 0
        mark(bit, r)
    return near, second


def build_lift(h: list[int], near: list[int], second: list[int]) -> tuple[list, list, list, int]:
    """倍增表：g[k][i] 从城市 i 出发走 2^k 轮（小A一段+小B一段）到达的城市，
    da/db 分别是这些轮里小A、小B 的里程；走不完的轮用 INF 代价标记。"""
    n = len(h) - 1
    rounds = max(1, (n - 1).bit_length())  # 2^rounds > n-1，任何合法轮数都能二进制拆分
    g = [[0] * (n + 1) for _ in range(rounds)]
    da = [[INF] * (n + 1) for _ in range(rounds)]
    db = [[INF] * (n + 1) for _ in range(rounds)]
    for i in range(1, n + 1):
        s = second[i]
        if not s:  # 小A没有第二近可选：一轮都开不起来
            continue
        da[0][i] = abs(h[i] - h[s])  # 第 1 天：小A开到次近城市
        t = near[s]                  # 第 2 天：小B在小A落点处接棒
        if t:
            db[0][i] = abs(h[s] - h[t])  # 小B开到最近城市
            g[0][i] = t
    for k in range(1, rounds):
        for i in range(n + 1):
            m = g[k - 1][i]          # 前半轮落点，后半轮从那里接着走
            g[k][i] = g[k - 1][m]
            da[k][i] = da[k - 1][i] + da[k - 1][m]
            db[k][i] = db[k - 1][i] + db[k - 1][m]
    return g, da, db, rounds


def drive(start: int, budget: int, g: list, da: list, db: list, rounds: int) -> tuple[int, int]:
    """从 start 出发、预算 budget，返回 (小A总里程, 小B总里程)。"""
    city, remain, total_a, total_b = start, budget, 0, 0
    for k in range(rounds - 1, -1, -1):  # 从大到小贪心跳跃，装下尽可能多的整轮
        cost = da[k][city] + db[k][city]
        if cost <= remain:
            total_a += da[k][city]
            total_b += db[k][city]
            remain -= cost
            city = g[k][city]
    # 整轮都放不下后，小A还能单独再开一段（此后小B必然接不上，旅程结束）
    if da[0][city] <= remain:
        total_a += da[0][city]
    return total_a, total_b


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    h = [0] + [next(data) for _ in range(n)]
    x0 = next(data)
    m = next(data)
    queries = [(next(data), next(data)) for _ in range(m)]

    near, second = nearest_two(h)
    g, da, db, rounds = build_lift(h, near, second)

    # 第一问：枚举起点，比值取最小；b=0 视为无穷大，无穷大之间相等，同比值取海拔更高者
    ranked = []
    for start in range(1, n + 1):
        total_a, total_b = drive(start, x0, g, da, db, rounds)
        ranked.append((Fraction(total_a, total_b) if total_b else inf, -h[start], start))
    out = [str(min(ranked)[2])]

    for start, budget in queries:
        total_a, total_b = drive(start, budget, g, da, db, rounds)
        out.append(f"{total_a} {total_b}")
    print("\n".join(out))


if __name__ == "__main__":
    solve()
