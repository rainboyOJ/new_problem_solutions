#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 23:11
# update_at: 2026-10-01 23:20

# N 到 5000，O(N^3) 区间 DP 要 2.1e10 次转移，逐格写的 Python 循环撑不住；
# 即便用四边形不等式把转移压到约 2.5e7 次，逐格 Python 也还要 4 秒多。
# 四边形不等式把每个区间的断点收窄到 [p[i][j-1], p[i+1][j]]，而同一长度下各区间
# 待枚举的断点首尾相接、互不重叠，于是“逐区间取最小值”就是一次 minimum.reduceat，
# 整道题按区间长度递推 O(N) 轮，每轮全是 numpy 批量操作。

import sys

import numpy as np

IDX = np.int32  # 决策点与上三角表的下标 < 1.3e7，int32 足够；索引数组内存减半


def min_merge_cost(stone: np.ndarray) -> int:
    """链上石子合并的最小总代价：区间 DP + 四边形不等式优化，O(n^2) 时间与空间。

    f[i][j] 是把区间 [i, j] 合并成一堆的最小代价。最后一次合并必然把区间劈成
    [i, k] 与 [k+1, j]，这次合并自身要付 S(i, j)（= ps[j+1] - ps[i]，与 k 无关），
    于是 f[i][j] = min_{i<=k<j} (f[i][k] + f[k+1][j]) + S(i, j)。

    合并代价 S 满足四边形不等式，最优断点 p[i][j] 随区间单调，即
    p[i][j-1] <= p[i][j] <= p[i+1][j]；两个端点都是更短区间在上层算好的值，
    故枚举范围收缩为 [p[i][j-1], p[i+1][j]]，全部区间的转移次数合计 O(n^2)。
    """
    n = stone.size
    ps = np.zeros(n + 1, dtype=np.int64)
    np.cumsum(stone, out=ps[1:])                    # ps[i] = 前 i 堆的质量和
    start = np.arange(n + 1, dtype=np.int64)        # 上三角逐个区间存：第 i 行放 f[i][i..n-1]
    base = (start * n - start * (start - 1) // 2).astype(IDX)  # 第 i 行的起始偏移
    f = np.zeros((n + 1) * (n + 1) // 2, dtype=np.int32)       # f[i][j] 落在 base[i] + (j - i)
    # 第 n 行是“空区间”哨兵行：f[k+1][j] 在 k = j 时落到它，值恒为 0，正好就是空区间的代价。
    dec = np.arange(n, dtype=IDX)                   # 上一层（长度 1 的区间）的最优断点

    for length in range(2, n + 1):
        m = n - length + 1                          # 这个长度下区间个数，左端点 i = 0..m-1
        lo, hi = dec[:m], dec[1:m + 1]              # p[i][j-1] 与 p[i+1][j]，断点下界与上界
        counts = hi - lo + 1                        # 每个区间要试的断点个数
        segs = np.cumsum(counts, dtype=IDX) - counts
        rows = np.repeat(np.arange(m, dtype=IDX), counts)       # 候选断点所属的区间左端 i
        ks = np.arange(int(counts.sum()), dtype=IDX)            # 全部候选断点拼成一条长链
        ks -= np.repeat(segs, counts)                           # 减去所在区间的起点
        ks += np.repeat(lo, counts)                             # 就是区间内的断点 k
        end = rows + (length - 1)                   # 区间右端 j；S(rows, end) = ps[end+1] - ps[rows]
        # 候选值 f[i][k] + f[k+1][j]：两下标都落在 i <= j 的上三角里，越界时落到第 n 行的空区间哨兵 0。
        # 每个 f 是“被合并元素 × 某段和”，总和不超过 b·n²，b <= 1000 时 < 4.7e8，int32 装得下。
        cost = f[base[rows] + (ks - rows)] + f[base[ks + 1] + (end - ks - 1)]
        best = np.minimum.reduceat(cost, segs)      # 每个区间的最小“左右两段代价之和”
        hit = np.flatnonzero(cost == np.repeat(best, counts))   # 该区间内达到最小值的候选
        dec = ks[hit[np.searchsorted(hit, segs)]]   # 取第一个（最小的）最优断点，作为区间决策
        f[base[:m] + (length - 1)] = best + (ps[length:length + m] - ps[:m])  # 补上最后一次合并

    return int(f[n - 1])  # n = 1 时就是 f[0] = 0：只有一堆，不需要任何合并


def solve() -> None:
    data = np.fromstring(sys.stdin.buffer.read(), dtype=np.int64, sep=" ")
    n = int(data[0])
    print(min_merge_cost(data[1:1 + n]))


if __name__ == "__main__":
    solve()
