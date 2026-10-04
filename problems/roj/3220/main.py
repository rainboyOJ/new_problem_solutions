#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 02:47
# update_at: 2026-10-02 03:30

import sys

FAR = 10 ** 18  # 松弛量初值：比任何曼哈顿距离都大，表示「还没连到交错树上」


def min_cost_perfect_matching(cost: list[list[int]]) -> int:
    """匈牙利算法（KM）：求 n×n 最小权完美匹配，返回最小总权值。

    顶标维持可行性 pot_l[i] + pot_r[j] <= cost[i][j]，取等号的边构成「相等子图」。
    只要相等子图里有完美匹配，每条匹配边都顶着等式取到下界，和必为全局最小。
    每轮把一个人 i 挂入交错树找增广路；找不到时给树上点整体改顶标：
    左部点 +delta、右部点 -delta（delta 是树到树外房子的最小松弛量），
    相等边一加一减保持不动，树外松弛量同步减 delta，至少冒出一条新等式边且可行性不破。
    """
    n = len(cost)
    pot_l = [0] * (n + 1)   # 左部（小人）顶标
    pot_r = [0] * (n + 1)   # 右部（房子）顶标
    match_r = [0] * (n + 1)  # match_r[j] = 配到房子 j 的小人，0 表示空房
    prev = [0] * (n + 1)     # 交错树上房子 j 的前驱房子

    for i in range(1, n + 1):
        match_r[0] = i        # 虚拟房子 0 指向本轮待增广的小人 i，当树根
        slack = [FAR] * (n + 1)   # 树外房子 j 到树上小人的最小松弛量
        used = [False] * (n + 1)
        j0 = 0
        while True:
            used[j0] = True
            row = cost[match_r[j0] - 1]   # 沿匹配边回退到的树上小人
            delta, j1 = FAR, 0
            for j in range(1, n + 1):      # 用新入树的小人刷新松弛量
                if not used[j]:
                    gap = row[j - 1] - pot_l[match_r[j0]] - pot_r[j]
                    if gap < slack[j]:
                        slack[j], prev[j] = gap, j0
                    if slack[j] < delta:
                        delta, j1 = slack[j], j
            for j in range(n + 1):         # 树上左 +delta 右 -delta，树外松弛量减 delta
                if used[j]:
                    pot_l[match_r[j]] += delta
                    pot_r[j] -= delta
                else:
                    slack[j] -= delta
            j0 = j1
            if match_r[j0] == 0:           # 撞上空房 = 找到增广路
                break
        while j0:                          # 沿 prev 翻转整条增广路
            match_r[j0] = match_r[prev[j0]]
            j0 = prev[j0]

    return sum(cost[match_r[j] - 1][j - 1] for j in range(1, n + 1))


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    while True:
        n, m = int(next(data)), int(next(data))
        if n == 0 and m == 0:                    # 题面约定的结束标记
            break
        grid = [next(data) for _ in range(n)]
        people = [(r, c) for r in range(n) for c in range(m) if grid[r][c] == ord('m')]
        houses = [(r, c) for r in range(n) for c in range(m) if grid[r][c] == ord('H')]
        # 权值取曼哈顿距离：空地、房门格都能踩，最短步数就是 |dr| + |dc|
        cost = [[abs(pr - hr) + abs(pc - hc) for hr, hc in houses] for pr, pc in people]
        out.append(str(min_cost_perfect_matching(cost)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
