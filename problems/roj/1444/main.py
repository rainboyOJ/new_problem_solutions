#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 10:54
# update_at: 2026-09-30 10:54

import sys
from math import gcd


def egypt_search(a: int, b: int, limit: int) -> tuple[int, ...] | None:
    """用恰好 limit 个互不相同的单位分数凑出 a/b，返回分母序列最优的一组，无解返回 None。

    序列比较规则：先比最大分母（越小则最小的分数 1/x_k 越大），
    再把整个分母序列从小到大做字典序比较，越小越优。
    """
    best: tuple[int, ...] | None = None

    def dfs(k: int, a: int, b: int, last: int, chosen: list[int]) -> None:
        """还剩 k 个加数要凑出 a/b，已选分母都小于等于 last，chosen 是当前路径。"""
        nonlocal best
        if k == 1:
            # 只剩一个加数时必须恰好相等：1/x = a/b ⟺ x = b/a（要求 b 是 a 的倍数）
            if b % a == 0:
                x = b // a
                if x > last:
                    seq = tuple(chosen + [x])
                    # (最大分母, 整个序列) 一起比：先保最大分母最小，再保字典序最小
                    if best is None or (seq[-1], seq) < (best[-1], best):
                        best = seq
            return
        lo = max(last + 1, b // a + 1)  # 1/x ≥ a/b 会立刻超额或把余量取空，排除
        hi = k * b // a                 # 连 k 个 1/x 都凑不满 a/b 的分母，排除
        for x in range(lo, hi + 1):
            na, nb = a * x - b, b * x   # a/b - 1/x = (ax-b)/(bx)
            g = gcd(na, nb)
            chosen.append(x)
            dfs(k - 1, na // g, nb // g, x, chosen)
            chosen.pop()

    dfs(limit, a, b, 0, [])
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    a, b = next(data), next(data)
    g = gcd(a, b)
    a, b = a // g, b // g            # 先约分，搜索状态里保持最简分数
    for limit in range(1, 10):       # IDA*：加数个数从 1 开始逐层加深
        best = egypt_search(a, b, limit)
        if best is not None:
            print(*best)
            return


if __name__ == "__main__":
    solve()
