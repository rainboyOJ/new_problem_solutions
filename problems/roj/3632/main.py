#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 12:05
# update_at: 2026-10-04 13:32

import sys

MOD = 1000000007


def count_plans(A: str, B: str, k: int) -> int:
    """从 A 中取 k 个互不重叠子串按序拼出 B 的方案数（对 MOD 取模）。

    f[j][t]：已扫描的 A 前缀能拼出 B[:j]、取 t+1 段的总方案数（A 当前字符用不用均可）；
    g[j][t]：在 f 的基础上额外要求最后一段以刚扫过的那个 A 字符匹配 B[j-1] 结尾。

    A[i] 与 B[j-1] 匹配时 g 才非零，转移恰有两种：接在当前段尾用 g[j-1][t]，
    让 A[i] 开新段用 f[j-1][t]（即凑 B[:j-1] 只用 t 段，新段从 A[i] 起步）。
    """
    # B 中每个字符出现的列号（1-based）：扫描 A 时只访问可能匹配的列
    cols_of: dict[str, list[int]] = {}
    for col, ch in enumerate(B, 1):
        cols_of.setdefault(ch, []).append(col)

    zero = [0] * k
    # f[0][t] 恒为 0：空串 B[:0] 取正段数不可能；第 0 列永远不更新
    f: list[list[int]] = [[0] * k for _ in range(len(B) + 1)]
    g_prev: list[list[int]] = [zero] * (len(B) + 1)  # 上一个 A 字符处的 g

    for ch in A:
        # 列号从右往左更新，读到的 f[col-1] 才会停留在上一个字符的那一层
        g_cur: list[list[int]] = [zero] * (len(B) + 1)
        for col in reversed(cols_of.get(ch, ())):
            seg_one_start = 1 if col == 1 else 0  # f[·][0][0]：0 段拼出空串恰有 1 种
            # 逐段位合并"接段尾 + 开新段"；两数都 < MOD，和减一次 MOD 即回 [0, MOD)
            joined = [
                v - MOD if (v := x + y) >= MOD else v
                for x, y in zip(g_prev[col - 1], [seg_one_start] + f[col - 1][:k - 1])
            ]
            f[col] = [v - MOD if (v := x + y) >= MOD else v for x, y in zip(f[col], joined)]
            g_cur[col] = joined
        g_prev = g_cur

    return f[len(B)][k - 1]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n, m, k = int(next(data)), int(next(data)), int(next(data))  # 题面的 |A|、|B| 与段数，转移只依赖 k
    print(count_plans(next(data).decode(), next(data).decode(), k))


if __name__ == "__main__":
    solve()
