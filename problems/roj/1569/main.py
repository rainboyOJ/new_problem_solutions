#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 19:25
# update_at: 2026-09-30 19:25

import sys

INF = 10 ** 9  # 最小值表的哨兵：比任何合法得分（总和 <= 200*10^9）都小的上界由 BIG 保证


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    stone = data[1:1 + n]
    BIG = sum(stone) * n + 1  # 任何方案得分都 <= n * 总和，用它当正无穷

    # 环形 → 链形：把序列接一份在后面，长度为 m 的区间就覆盖了任意环形起点的 m 堆
    a = stone * 2
    m = 2 * n  # 实际只用前 m 个下标；区间 [i, j] 表示第 i..j 堆合并成一堆

    # pre[k] = 前 k 堆的和，区间得分用 pre[j+1]-pre[i] 一次减出来
    pre = [0] * (m + 1)
    for k in range(m):
        pre[k + 1] = pre[k] + a[k]

    # f[i][j] / g[i][j]：把 [i, j] 合并成一堆的最小 / 最大得分
    f = [[0] * m for _ in range(m)]
    g = [[0] * m for _ in range(m)]

    for length in range(2, n + 1):  # 合并 length 堆；length=1 的区间本身不用花钱
        for i in range(m - length + 1):
            j = i + length - 1
            total = pre[j + 1] - pre[i]  # 最后一次合并必得的分：两段之和就是整段和
            best_min, best_max = BIG, -1
            for k in range(i, j):  # 枚举断点：左段 [i,k] 与右段 [k+1,j] 先各自成堆
                left_min, left_max = f[i][k], g[i][k]
                right_min, right_max = f[k + 1][j], g[k + 1][j]
                s_min = left_min + right_min
                s_max = left_max + right_max
                if s_min < best_min:
                    best_min = s_min
                if s_max > best_max:
                    best_max = s_max
            f[i][j] = best_min + total
            g[i][j] = best_max + total

    # 拆环的每个位置 r 都是候选起点，起点固定的链长 n 区间 [r, r+n-1] 就是该方案
    print(min(f[r][r + n - 1] for r in range(n)))
    print(max(g[r][r + n - 1] for r in range(n)))


if __name__ == "__main__":
    solve()
