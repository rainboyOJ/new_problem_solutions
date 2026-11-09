#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-11-09 17:35
# update_at: 2026-11-09 17:35

import sys

INF = 10**9  # 表示「该前缀涂不到」

# 每个区间 [l, r] 用 (左端点 l, 右端点 r, 字符串编号 w, 起始位置 p) 表示，下标 0 起
type Seg = tuple[int, int, int, int]
# 前驱：从哪个前缀位置转移来、用了哪个字符串、从哪开始（下标 0 起）
type Pre = tuple[int, int, int]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    q = int(next(data))

    for _ in range(q):
        t = next(data).decode()
        n = int(next(data))
        strs = [next(data).decode() for _ in range(n)]
        length = len(t)

        segs: list[Seg] = sorted(
            (p, p + len(s) - 1, w, p)
            for w, s in enumerate(strs, 1)
            for p in range(length - len(s) + 1)
            if t.startswith(s, p)
        )

        # dp[i] = 涂红前缀 t[0..i-1] 的最少步数；pre[i] 记录来源用于回溯方案
        dp = [INF] * (length + 1)
        pre: list[Pre | None] = [None] * (length + 1)
        dp[0] = 0

        for i in range(length):
            if dp[i] == INF:
                continue
            for l, r, w, p in segs:
                if l > i:                          # 左端点必须落在已涂红前缀内（允许重叠）
                    break
                reach = max(i, r + 1)              # 涂红后推进到的前缀终点
                if dp[i] + 1 < dp[reach]:
                    dp[reach] = dp[i] + 1
                    pre[reach] = (i, w, p)

        if dp[length] == INF:                      # 涂不满所有字母
            out.append("-1")
            continue

        plan: list[tuple[int, int]] = []
        cur = length
        while cur > 0:                             # 沿前驱回溯，得到逆序方案
            prev_i, w, p = pre[cur]
            plan.append((w, p + 1))
            cur = prev_i

        out.append(str(len(plan)))
        out += [f"{w} {p}" for w, p in reversed(plan)]

    print("\n".join(out))


if __name__ == "__main__":
    solve()
