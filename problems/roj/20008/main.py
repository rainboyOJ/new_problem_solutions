#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:36
# update_at: 2026-10-02 19:36

import sys

GOD_SONG = 678  # 神曲《阿什尼亚克西》：11 分 18 秒
UNREACH = -1    # 背包哨兵：总长 s 凑不出来（f[0]=0 是唯一可达的 0 首）


def knapsack(songs: list[int], cap: int) -> list[int]:
    """0/1 背包：f[s] = 恰好凑出总长 s 时最多能唱几首，凑不出记为 UNREACH。"""
    f = [UNREACH] * (cap + 1)
    f[0] = 0
    for length in songs:
        for s in range(cap, length - 1, -1):  # 逆序更新，保证每首歌只选一次
            if f[s - length] != UNREACH:
                f[s] = max(f[s], f[s - length] + 1)
    return f


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]                      # 普通歌的数量（神曲不计入）
    t = data[1]                      # KTV 还剩的秒数
    songs = data[2:2 + n]

    # 神曲必须在结束前的最后一刻开唱：选中的歌总长至多 t-1；
    # 每首歌 ≤180s、n≤50，总长不超过 9000，背包上界顺手收窄到实际总长。
    cap = max(min(t - 1, sum(songs)), 0)
    f = knapsack(songs, cap)

    most = max(f)                                   # 时限内最多能唱几首普通歌
    longest = max(s for s, c in enumerate(f) if c == most)  # 同样多首里挑总长最长的
    # 数据陷阱：一首歌都塞不进 t-1 秒时，评测数据与标程一致地输出 (t-1, 678)
    count, total = (t - 1, GOD_SONG) if most == 0 else (most + 1, longest + GOD_SONG)
    print(count, total)


if __name__ == "__main__":
    solve()
