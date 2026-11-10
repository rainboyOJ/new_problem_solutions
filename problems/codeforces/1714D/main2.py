#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-11-09 17:35
# update_at: 2026-11-10 10:30

import sys
from collections.abc import Iterator

INF = 10**9  # 表示该前缀目前不可达

# 匹配区间：(左端点 l, 右端点 r, 单词序号 w, 1 起起始位置 p)，半开区间 [l, r)
type Match = tuple[int, int, int, int]
# 转移前驱：(上一前缀长度 prev_i, 单词序号 w, 1 起起始位置 p)
type Step = tuple[int, int, int]
type Plan = list[tuple[int, int]]


def occurrences(t: str, s: str) -> Iterator[int]:
    """产出子串 s 在 t 中的所有起始位置（允许重叠）。"""
    p = t.find(s)
    while p != -1:
        yield p
        p = t.find(s, p + 1)


def min_color_dp(t: str, words: list[str]) -> Plan | None:
    """用 DP 计算将 t 涂红的最少区间方案；若无法涂满返回 None。"""
    matches: list[Match] = [
        (p, p + len(s), w, p + 1)
        for w, s in enumerate(words, 1)
        for p in occurrences(t, s)
    ]

    n = len(t)
    # dp[i] 表示染红前缀 [0, i) 所需的最少操作步数
    dp = [0] + [INF] * n
    pre: list[Step | None] = [None] * (n + 1)

    for i in range(n):
        if dp[i] == INF:
            continue
        cost = dp[i] + 1
        for l, r, w, p in matches:
            # 区间覆盖当前末端点 i（l <= i < r），可将前缀延伸到 r
            if l <= i < r and cost < dp[r]:
                dp[r] = cost
                pre[r] = (i, w, p)

    if dp[n] == INF:
        return None

    # 从终点 n 沿前驱回溯最优路径
    plan: Plan = []
    cur = n
    while cur > 0:
        assert pre[cur] is not None
        cur, w, p = pre[cur]
        plan.append((w, p))

    return plan[::-1]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    q = int(next(data))

    for _ in range(q):
        t = next(data).decode()
        n = int(next(data))
        words = [next(data).decode() for _ in range(n)]

        plan = min_color_dp(t, words)
        if plan is None:
            out.append("-1")
        else:
            out.append(str(len(plan)))
            out.extend(f"{w} {p}" for w, p in plan)

    print("\n".join(out))


if __name__ == "__main__":
    solve()
