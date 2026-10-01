#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 18:28
# update_at: 2026-10-01 18:28

import numpy as np
import sys

T = 1000  # 分块大小：位置按每 T 个分成一块，块内散元素 ≤ 2T 个逐个补偿


def block_pair_table(bc: np.ndarray, blocks: int) -> list[list[int]]:
    """g[i][j] = 完整块区间 [i, j] 内出现正偶数次的数值个数。

    逐行递增右端块：往 [i, j-1] 的计数里并入第 j 块，
    只有第 j 块里出现过的值状态可能变化，增量只在这些值上算。
    """
    g = [[0] * blocks for _ in range(blocks)]
    cnt = np.zeros(bc.shape[1], np.int32)  # 值 → 在块 [i, j] 中的出现次数
    for i in range(blocks):
        cnt[:] = 0
        cur = 0
        row = g[i]
        for j in range(i, blocks):
            nz = np.nonzero(bc[j])[0]          # 第 j 块里出现过的值
            before = cnt[nz]
            after = before + bc[j][nz]
            cnt[nz] = after
            # 状态函数 f(x) = (x 为正偶数)：新状态转 1、旧状态转 1，差值即增量
            cur += int((((after & 1) == 0) & (after >= 2)).sum()
                       - (((before & 1) == 0) & (before >= 2)).sum())
            row[j] = cur
    return g


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    nums = list(map(int, data))
    n, c, m = nums[0], nums[1], nums[2]
    a = np.array(nums[3:3 + n], dtype=np.int32)
    qs = nums[3 + n:]

    blocks = (n + T - 1) // T
    bc = np.zeros((blocks, c + 1), np.int32)  # 每块内各值的出现次数
    np.add.at(bc, (np.arange(n) // T, a), 1)
    pre = np.zeros((blocks + 1, c + 1), np.int32)  # pre[i][v] = 前 i 块中 v 的次数
    np.cumsum(bc, axis=0, out=pre[1:])

    # 把 (值, 位置) 编码成一个 int64 键后全局排序：值 v 在位置区间 [lo, hi]
    # 的出现次数 = 二分键 v*(n+1)+hi+1 与 v*(n+1)+lo 的差，可对整组值向量化
    keys = np.sort(a.astype(np.int64) * (n + 1) + np.arange(n, dtype=np.int64))
    g = block_pair_table(bc, blocks)

    out: list[str] = []
    ans = 0  # 上一个询问的答案，强制在线解密用
    n1 = n + 1
    for q in range(m):
        l = (qs[2 * q] + ans) % n           # 题面 L=(l+ans) mod n+1，转 0 下标后即 mod n
        r = (qs[2 * q + 1] + ans) % n
        if l > r:
            l, r = r, l
        bl, br = l // T, r // T

        if br - bl < 2:  # 中间没有完整块：整段当作散段直接统计
            vu = np.unique(a[l:r + 1])
            key = vu.astype(np.int64) * n1
            t = np.searchsorted(keys, key + r + 1) - np.searchsorted(keys, key + l)
            ans = int((((t & 1) == 0) & (t >= 2)).sum())
        else:
            # 两侧散段的互异值：先在完整块答案上做补偿
            idx = np.concatenate((np.arange(l, (bl + 1) * T), np.arange(br * T, r + 1)))
            vu = np.unique(a[idx])
            key = vu.astype(np.int64) * n1
            tin = pre[br][vu] - pre[bl + 1][vu]              # 该值在中间完整块 bl+1..br-1 的次数
            cl = (np.searchsorted(keys, key + (bl + 1) * T)
                  - np.searchsorted(keys, key + l))          # 左散段次数
            cr = (np.searchsorted(keys, key + r + 1)
                  - np.searchsorted(keys, key + br * T))     # 右散段次数
            t = tin + cl + cr
            # 总次数为正偶数 → 加 1；只在中间块里算成过正偶数 → 撤回 1
            ans = (g[bl + 1][br - 1]
                   + int((((t & 1) == 0) & (t >= 2)).sum()
                         - (((tin & 1) == 0) & (tin >= 2)).sum()))
        out.append(str(ans))

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
