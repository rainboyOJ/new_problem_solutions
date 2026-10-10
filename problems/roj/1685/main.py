#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:27
# update_at: 2026-10-07 15:27

import sys

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type States = dict[int, int]  # 某个已取集合下"当前停在哪格 -> 该集合的最大得分"
type Nbrs = list[list[int]]   # 邻接表：nbrs[i] 是格子 i 四个方向里仍在方格内的相邻格编号


def max_score(values: list[int], nbrs: Nbrs, on_edge: list[bool], edge: list[int]) -> int:
    """状压 DP，回答"最大总得分是多少"。

    dp[S][p] = 已取格集合为 S、当前停在格 p 时的最大得分。转移有两类：
    走到相邻未取格；当前在边缘格时离开方格，从任一未取边缘格重新进入。
    第 k 次取走的格 q 得分 k * values[q]，所以用 S.bit_count() + 1 直接乘。
    """
    total = len(values)
    dp: dict[int, States] = {}
    for p in edge:                 # 第 1 次取数必须从边缘格入手，得 1 * values[p]
        dp[1 << p] = {p: values[p]}

    for mask in range(1 << total):  # 集合只增不减，按掩码从小到大推进就是拓扑序
        states = dp.get(mask)
        if not states:              # 该集合一个状态都到不了，跳过
            continue
        k = mask.bit_count() + 1     # 下一个取走的数是第 k 个
        for p, cur in states.items():
            moves = [q for q in nbrs[p] if not mask >> q & 1]   # 走到相邻未取格
            if on_edge[p]:                                      # 停在边缘：可离格再入口
                moves += [q for q in edge if not mask >> q & 1]
            for q in moves:
                nxt = cur + k * values[q]
                # 所有可达状态得分都非负，用 0 当"尚未到达"的下界即可，真到达时只会更大
                nxt_states = dp.setdefault(mask | 1 << q, {})
                nxt_states[q] = max(nxt_states.get(q, 0), nxt)

    scores = [v for st in dp.values() for v in st.values()]
    return max(scores, default=0)  # 游戏可随时结束，一个数都不取时得 0 分


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n = next(data), next(data)
    total = m * n
    values = [next(data) for _ in range(total)]

    cells = [divmod(i, n) for i in range(total)]           # 每格展平编号 -> (行, 列)
    on_edge = [r in (0, m - 1) or c in (0, n - 1) for r, c in cells]
    edge = [i for i, ok in enumerate(on_edge) if ok]        # 所有边缘格的编号

    nbrs: Nbrs = []
    for i, (r, c) in enumerate(cells):
        around = ((i - n, r > 0), (i + n, r < m - 1),         # 上、下
                  (i - 1, c > 0), (i + 1, c < n - 1))         # 左、右
        nbrs.append([j for j, inside in around if inside])    # 只留还在方格内的方向

    print(max_score(values, nbrs, on_edge, edge))


if __name__ == "__main__":
    solve()
