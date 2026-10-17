#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-17 22:52
# update_at: 2026-10-17 22:58
#
# 静态矩形覆盖计数：扫描线 + 树状数组（rbook_nunjucks 代码模板风格）。
# 矩形是半开的 [l, r) x [d, u)。按 x 扫描：
#   x = l 处对 y 区间 [d, u) 加 1（矩形进入扫描线）
#   x = r 处对 y 区间 [d, u) 减 1（矩形离开扫描线）
# 同一 x 先做矩形事件、再回答询问，于是 x == l 已算覆盖、x == r 已不算覆盖。
# y 方向用「差分 + 树状数组」，区间加变两次单点加，单点查变一次前缀和。
# 坐标全部 1 下标（离散化后的名次也从 1 开始）：lowbit(0) = 0 会让修改循环原地打转。

import sys

type Seq = list[int]  # 1 下标 int 序列，下标 0 占位不用


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    pos = 0

    n = data[pos]
    m = data[pos + 1]
    pos += 2

    # 矩形 (l, d, r, u)；同时收集 y 方向要离散化的坐标
    rects: list[tuple[int, int, int, int]] = []
    ys: Seq = [0]  # 下标 0 占位
    for _ in range(n):
        l, d, r, u = data[pos], data[pos + 1], data[pos + 2], data[pos + 3]
        pos += 4
        rects.append((l, d, r, u))
        ys.append(d)
        ys.append(u)

    # 询问点 (x, y)
    queries: list[tuple[int, int]] = []
    for _ in range(m):
        x, y = data[pos], data[pos + 1]
        pos += 2
        queries.append((x, y))
        ys.append(y)

    # y 离散化：值 -> 1 起的名次
    ordered = sorted(set(ys[1:]))
    rank = {v: i for i, v in enumerate(ordered, start=1)}
    ys_cnt = len(ordered)

    # 事件统一成 7 元组，直接靠元组比较排序：
    #   (x, kind, sign, lo, hi, y, id)
    #   kind = 0 矩形事件：sign = ±1，影响离散化区间 [lo, hi)
    #   kind = 1 询问事件：查离散化名次为 y 的位置，编号 id
    # kind 放在第二关键字，保证同一 x 上矩形事件先于询问事件。
    events: list[tuple[int, int, int, int, int, int, int]] = []
    for l, d, r, u in rects:
        lo = rank[d]
        hi = rank[u]
        events.append((l, 0, 1, lo, hi, 0, 0))   # 从 l 开始覆盖
        events.append((r, 0, -1, lo, hi, 0, 0))  # 到 r 就不覆盖了
    for j, (x, y) in enumerate(queries):
        events.append((x, 1, 0, 0, 0, rank[y], j))
    events.sort()

    tree: Seq = [0] * (ys_cnt + 1)  # 树状数组维护 y 方向的差分数组
    answer: Seq = [0] * m

    for x, kind, sign, lo, hi, y, idx in events:
        if kind == 0:
            # 差分：区间 [lo, hi) 加 sign = lo 处 +sign、hi 处 -sign
            i = lo
            while i <= ys_cnt:
                tree[i] += sign
                i += i & -i
            i = hi
            while i <= ys_cnt:
                tree[i] -= sign
                i += i & -i
        else:
            # 差分前缀和 = 该 y 处当前被多少个矩形覆盖
            total = 0
            i = y
            while i > 0:
                total += tree[i]
                i -= i & -i
            answer[idx] = total

    sys.stdout.write("\n".join(map(str, answer)) + "\n")


if __name__ == "__main__":
    solve()
