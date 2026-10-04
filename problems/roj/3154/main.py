#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 21:19
# update_at: 2026-10-01 21:39

import sys
from array import array

# 城市编号从 1 开始，0 统一表示「不存在 / 无法前进」的哨兵。


def choose_targets(h: list[int]) -> tuple[list[int], list[int]]:
    """返回 (na, nb)：na[i] / nb[i] 是小A / 小B 从 i 向东要去的城市。

    把城市按海拔排成双向链表后，距离最近、次近的候选只会藏在海拔相邻的
    至多 4 个城市里；按编号从西往东处理并删掉已处理城市，
    链表里剩下的恰好都是东边的城市。
    """
    n = len(h) - 1
    order = sorted(range(1, n + 1), key=lambda c: h[c])
    west = [0] * (n + 1)  # 海拔排序链表的左 / 右邻居
    east = [0] * (n + 1)
    for prev, cur in zip(order, order[1:]):
        east[prev] = cur
        west[cur] = prev

    na = [0] * (n + 1)
    nb = [0] * (n + 1)
    for i in range(1, n + 1):
        cand = []
        j = west[i]
        for _ in range(2):  # 海拔方向两侧各取 2 个候选
            if j:
                cand.append(j)
                j = west[j]
        j = east[i]
        for _ in range(2):
            if j:
                cand.append(j)
                j = east[j]
        # 距离相同时海拔低者算更近，所以排序后第 1 个给小B、第 2 个给小A
        cand.sort(key=lambda c: (abs(h[i] - h[c]), h[c]))
        nb[i] = cand[0] if cand else 0
        na[i] = cand[1] if len(cand) > 1 else 0
        east[west[i]] = east[i]  # 删掉 i，链表里剩下的全是东边城市
        west[east[i]] = west[i]
    return na, nb


def build_tables(na: list[int], nb: list[int], h: list[int]) -> tuple[int, list, list, list]:
    """建倍增表，返回 (log, nxt, da, db)。

    nxt[k][w][i]：从 i 出发、由 w（0=小A，1=小B）先开，走 2^k 步后到达的城市；
    da / db 同布局，记录这 2^k 步里两人各自的里程。
    后 2^(k-1) 步的先开者：k=1 时只剩 1 步要换人，k>=2 时走偶数步不换人。
    """
    n = len(h) - 1
    log = max(1, (n - 1).bit_length())  # 任意旅程步数 <= n-1，2^log 足够覆盖
    nxt = [[array('i', [0]) * (n + 1) for _ in range(2)] for _ in range(log)]
    da = [[array('q', [0]) * (n + 1) for _ in range(2)] for _ in range(log)]
    db = [[array('q', [0]) * (n + 1) for _ in range(2)] for _ in range(log)]

    for i in range(1, n + 1):
        if na[i]:
            nxt[0][0][i] = na[i]
            da[0][0][i] = abs(h[i] - h[na[i]])
        if nb[i]:
            nxt[0][1][i] = nb[i]
            db[0][1][i] = abs(h[i] - h[nb[i]])

    for k in range(1, log):
        pre = k - 1
        for w in range(2):
            w2 = w ^ 1 if k == 1 else w  # 后一段的先开者只与 k 有关
            for i in range(1, n + 1):
                mid = nxt[pre][w][i]
                if mid:
                    nxt[k][w][i] = nxt[pre][w2][mid]
                    da[k][w][i] = da[pre][w][i] + da[pre][w2][mid]
                    db[k][w][i] = db[pre][w][i] + db[pre][w2][mid]
    return log, nxt, da, db


def drive(s: int, x: int, log: int, nxt: list, da: list, db: list) -> tuple[int, int]:
    """从 s 出发最多开 x 公里，返回（小A总里程，小B总里程）。"""
    a = b = 0
    cur = s
    w = 0  # 第一天小A先开
    for k in range(log - 1, -1, -1):
        step = da[k][w][cur] + db[k][w][cur]
        if nxt[k][w][cur] and a + b + step <= x:
            a += da[k][w][cur]
            b += db[k][w][cur]
            cur = nxt[k][w][cur]
            if k == 0:  # 只有 2^0 = 1 步是奇数步，才换司机
                w ^= 1
    return a, b


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    h = [0] + [next(data) for _ in range(n)]
    x0 = next(data)
    m = next(data)
    queries = [(next(data), next(data)) for _ in range(m)]

    na, nb = choose_targets(h)
    log, nxt, da, db = build_tables(na, nb, h)

    # 问题 1：枚举起点找 a/b 最小的出发城市；b=0 视为无穷大，同值比海拔
    best_s = 1
    best_a, best_b = drive(1, x0, log, nxt, da, db)
    for s in range(2, n + 1):
        a, b = drive(s, x0, log, nxt, da, db)
        if b == 0:
            take = best_b == 0 and h[s] > h[best_s]  # 两个无穷大之间比海拔
        elif best_b == 0:
            take = True  # 有限比值优于无穷大
        else:
            lhs, rhs = a * best_b, best_a * b  # 交叉相乘比较 a/b，避免浮点误差
            take = lhs < rhs or (lhs == rhs and h[s] > h[best_s])
        if take:
            best_s, best_a, best_b = s, a, b

    out = [str(best_s)]
    for s, x in queries:  # 问题 2：逐个询问模拟
        a, b = drive(s, x, log, nxt, da, db)
        out.append(f'{a} {b}')
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
