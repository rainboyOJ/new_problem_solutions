#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:54
# update_at: 2026-10-02 11:20

import sys

INF = 10**9   # 最少点击数的不可达哨兵：任一合法路径点击数不超过 n*m <= 1e7


def rise(nxt_tap: list[int], nxt_cnt: list[int], tap: list[int], cnt: list[int], dx: int, m: int) -> None:
    """上升转移：本单位时间至少点一次，多次点击效果叠加，到顶 m 封顶。

    按高度升序扫一遍即可传播"点 t 次"：写入 nxt_tap[t] 的是"从上一列点一次"，
    而 nxt_tap[h] 在轮到 h 时已经定型（只有下标 h-dx 会写它），所以
    `nxt_tap[h] + 1` 正是"同单位时间再叠一次"。此刻 nxt 里只有上升结果，
    链式叠加不会混入下降值。
    """
    for h in range(1, m + 1):
        t = h + dx
        if t > m:
            t = m                       # 到顶后再点也升不上去，统一收进 m
        v = tap[h] + 1                  # 上一列点一次到达 t
        if v < nxt_tap[t]:
            nxt_tap[t] = v
        if cnt[h] > nxt_cnt[t]:
            nxt_cnt[t] = cnt[h]
        w = nxt_tap[h] + 1              # 同一单位时间继续叠加点击
        if w < nxt_tap[t]:
            nxt_tap[t] = w
        if nxt_cnt[h] > nxt_cnt[t]:
            nxt_cnt[t] = nxt_cnt[h]


def fall(nxt_tap: list[int], nxt_cnt: list[int], tap: list[int], cnt: list[int], dy: int, m: int) -> None:
    """下降转移：一次也不点，整体下落 dy；落到 0 即坠毁，只保留高度 >= 1 的落点。"""
    tgt = slice(1, m - dy + 1)          # 落点 1..m-dy
    src = slice(dy + 1, m + 1)          # 起点 dy+1..m，落差正好 dy
    nxt_tap[tgt] = [a if a < b else b for a, b in zip(nxt_tap[tgt], tap[src])]
    nxt_cnt[tgt] = [a if a > b else b for a, b in zip(nxt_cnt[tgt], cnt[src])]


def pass_pipe(nxt_tap: list[int], nxt_cnt: list[int], gap: tuple[int, int], m: int) -> None:
    """过管转移：缝隙 (low, high) 外的高度撞管坠毁，缝隙内存活者通过计数 +1。"""
    low, high = gap
    nxt_tap[1:low + 1] = [INF] * low                # 撞下边沿及其下方
    nxt_tap[high:m + 1] = [INF] * (m + 1 - high)    # 撞上边沿及其上方
    nxt_cnt[1:low + 1] = [-1] * low
    nxt_cnt[high:m + 1] = [-1] * (m + 1 - high)
    # 计数只加在存活者身上：-1 表示该高度本就不可达
    nxt_cnt[low + 1:high] = [v + 1 if v >= 0 else -1 for v in nxt_cnt[low + 1:high]]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)                      # 界面长度：横坐标 0..n-1，走完 n 步到最右边
    m = next(data)                      # 界面高度：存活高度 1..m，0 即坠毁
    k = next(data)                      # 管道数

    # 每列一行 (X, Y)：点一次上升 X[x]，一次不点下降 Y[x]
    steps = [(next(data), next(data)) for _ in range(n)]

    # pipe_at[x] = (L, H)：缝隙是开区间 (L, H)，贴边即撞管
    pipe_at: list[tuple[int, int] | None] = [None] * n
    for _ in range(k):
        p, low, high = next(data), next(data), next(data)
        pipe_at[p] = (low, high)

    tap = [0] * (m + 1)                 # 当前列各高度的最少点击数（列 0 任选高度出发）
    cnt = [0] * (m + 1)                 # 当前列各高度的最多通过管道数
    best = 0                            # 全局最多通过数：路径随时可能坠毁，要逐列取最大

    for x in range(n):
        dx, dy = steps[x]                # 本列的上升/下降步长
        nxt_tap = [INF] * (m + 1)
        nxt_cnt = [-1] * (m + 1)
        rise(nxt_tap, nxt_cnt, tap, cnt, dx, m)
        fall(nxt_tap, nxt_cnt, tap, cnt, dy, m)

        # 落在下一列 x+1 的管道上：缝隙外坠毁，缝隙内通过计数 +1
        gap = pipe_at[x + 1] if x + 1 < n else None
        if gap is not None:
            pass_pipe(nxt_tap, nxt_cnt, gap, m)

        best = max(best, max(nxt_cnt))
        tap, cnt = nxt_tap, nxt_cnt

    fewest = min(tap[1:])               # 列 n：任一高度抵达即通关
    won = fewest < INF
    print(1 if won else 0)
    print(fewest if won else best)


if __name__ == "__main__":
    solve()
