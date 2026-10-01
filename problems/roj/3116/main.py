#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 18:14
# update_at: 2026-10-01 18:28

# 一次询问要统计整个区间的众数，逐次暴力是 O(n·m)，扛不住 4e4 × 5e4。
# 把序列切成约 sqrt(n) 个块后，「整块的众数」可以预处理，
# 而询问只剩两端不足一块的零散位置（< 2·sqrt(n) 个）需要现算。

import sys
from bisect import bisect_left, bisect_right
from math import isqrt


def prepare(raw: list[int]) -> tuple[list[int], list[int], list[list[int]], list[list[int]]]:
    """值压缩，并预处理每个值的出现位置与「整块区间众数」表。"""
    vals = sorted(set(raw))                       # 值去重后升序，压缩下标小 == 种类编号小
    rank = {v: i for i, v in enumerate(vals)}
    a = [rank[v] for v in raw]
    n, kinds = len(a), len(vals)
    block = max(1, isqrt(n))                      # 块大小取 sqrt(n)，块数与块长同为 O(sqrt(n))
    nblk = (n + block - 1) // block

    occ: list[list[int]] = [[] for _ in range(kinds)]   # occ[v] = v 的出现下标，升序
    for i, v in enumerate(a):
        occ[v].append(i)

    # mode[i][j] = 只看块 i..j 时的答案；j 递增时增量维护计数，避免每对块重新统计
    mode = [[0] * nblk for _ in range(nblk)]
    for i in range(nblk):
        cnt = [0] * kinds
        best = cur = 0                            # cur 是当前众数的种类下标
        for j in range(i, nblk):
            for v in a[j * block:(j + 1) * block]:
                cnt[v] += 1
                # 出现更多即换；出现一样多时下标更小才换（对应编号最小）
                if cnt[v] > best or (cnt[v] == best and v < cur):
                    best, cur = cnt[v], v
            mode[i][j] = cur
    return vals, a, occ, mode


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n, m = int(data[0]), int(data[1])
    vals, a, occ, mode = prepare(list(map(int, data[2:2 + n])))
    block = max(1, isqrt(n))

    ans: list[str] = []
    pos = 2 + n
    x = 0                                         # 上一次询问的答案（明文，用于解密下标）
    for _ in range(m):
        l = (int(data[pos]) + x - 1) % n
        r = (int(data[pos + 1]) + x - 1) % n
        pos += 2
        if l > r:
            l, r = r, l
        bl, br = l // block, r // block
        if bl == br:
            cand = set(a[l:r + 1])                # 两端落在同一块：整段都不足一块
        else:
            cand = set(a[l:(bl + 1) * block]) | set(a[br * block:r + 1])
            if br - 1 > bl:                       # 中间整块区间的众数只需和零散值比一比
                cand.add(mode[bl + 1][br - 1])
        best = -1                                 # 众数的种类下标
        bestc = -1
        for v in cand:
            c = bisect_right(occ[v], r) - bisect_left(occ[v], l)
            if c > bestc or (c == bestc and v < best):
                best, bestc = v, c
        x = vals[best]
        ans.append(str(x))
    sys.stdout.write('\n'.join(ans) + '\n')


if __name__ == "__main__":
    solve()
