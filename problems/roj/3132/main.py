#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 20:22
# update_at: 2026-10-01 20:22

import sys

MAX_BIT = 30  # Ai < 2^31，前缀异或的最高有效位是第 30 位

# 可持久化 01 Trie：节点 0 是空版本，CNT 是子树计数，CH0/CH1 是两个孩子编号
CNT: list[int] = [0]
CH0: list[int] = [0]
CH1: list[int] = [0]
RO: list[int] = [0]  # RO[k] = 插入 S[0..k-1] 之后的根；RO[0] 是空版本


def trie_extend(prev: int, x: int) -> int:
    """把前缀异或 x 插入 Trie，沿路复制出一个新版本并返回新版本的根。

    版本只增不删，所以同一位置的节点在两个版本里的计数差，
    就是两个版本之间插入的数在该分支上的个数。
    """
    root = len(CNT)
    CNT.append(CNT[prev] + 1)
    CH0.append(CH0[prev])  # 没走到的另一支原样共享
    CH1.append(CH1[prev])
    new_node, old_node = root, prev
    for k in range(MAX_BIT, -1, -1):
        bit = x >> k & 1
        old_child = CH0[old_node] if bit == 0 else CH1[old_node]
        node = len(CNT)
        CNT.append(CNT[old_child] + 1)          # 旧分支上的计数 + 本次插入
        CH0.append(CH0[old_child])              # 沿路复制，没走到的另一支原样共享
        CH1.append(CH1[old_child])
        if bit == 0:
            CH0[new_node] = node
        else:
            CH1[new_node] = node
        new_node, old_node = node, old_child
    return root


def range_max_xor(
    hi: int,
    lo: int,
    x: int,
    ro: list[int] = RO,
    cnt: list[int] = CNT,
    ch0: list[int] = CH0,
    ch1: list[int] = CH1,
) -> int:
    """前缀异或区间 S[lo..hi] 中，与 x 异或的最大值。

    两个版本根同时下钻：某分支的计数差大于 0 说明区间里有人走过，
    就贪心走能使结果这一位为 1 的方向。
    """
    u, v = ro[hi + 1], ro[lo]  # v 是 lo 之前的版本，作差得到区间
    best = 0
    for k in range(MAX_BIT, -1, -1):
        bit = x >> k & 1
        if bit:  # 想让结果这一位为 1 就走反方向 0
            pu, pv = ch0[u], ch0[v]
            if cnt[pu] > cnt[pv]:
                best |= 1 << k
                u, v = pu, pv
            else:
                u, v = ch1[u], ch1[v]
        else:  # 想走反方向 1
            pu, pv = ch1[u], ch1[v]
            if cnt[pu] > cnt[pv]:
                best |= 1 << k
                u, v = pu, pv
            else:
                u, v = ch0[u], ch0[v]
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    m = next(data)
    a = [next(data) for _ in range(n)]

    # 前缀异或 S[i] = A1 xor ... xor Ai，子段异或和 = S[i-1] xor S[j]
    s = [0] * (n + 1)
    for i in range(1, n + 1):
        s[i] = s[i - 1] ^ a[i - 1]

    for k in range(n + 1):  # 建 n+1 个版本，之后任意前缀区间都能两版本作差
        RO.append(trie_extend(RO[-1], s[k]))

    block = max(1, int(n ** 0.5))  # 块长 ~sqrt(N)：预处理 N^1.5、单次询问 N^0.5
    block_count = (n + block - 1) // block

    # g[i]：从 i 到所在块末尾的最大子段异或和，供询问左段 O(1) 取用
    g = [0] * (n + 1)
    for start in range(0, n, block):
        block_lo, block_hi = start + 1, min(start + block, n)
        best = 0
        for i in range(block_hi, block_lo - 1, -1):
            # 起点固定在 i-1，终点在 [i, 块末尾] 里挑
            best = max(best, range_max_xor(block_hi, i, s[i - 1]))
            g[i] = best

    # f[bi]：起点 >= bi*block+1 且终点 <= j 的最大子段异或和（base = bi*block+1）
    f: list[list[int]] = [[]]  # f[0] 占位：第一个完整块之前的起点用不上
    for bi in range(1, block_count):
        base = bi * block + 1
        row = [0] * (n - base + 1)
        best = 0
        for j in range(base, n + 1):
            # 终点固定在 j，起点在 [base, j] 里挑（含单元素 A[j]）
            best = max(best, range_max_xor(j - 1, base - 1, s[j]))
            row[j - base] = best
        f.append(row)

    out: list[str] = []
    last = 0  # 在线询问：上一问的答案参与下一问的解码
    for _ in range(m):
        x, y = next(data), next(data)
        p, q = (x + last) % n + 1, (y + last) % n + 1
        l, r = (p, q) if p <= q else (q, p)
        left_block, right_block = (l - 1) // block, (r - 1)// block
        if left_block == right_block:  # 同块：右端点最多扫一个块
            best = max(range_max_xor(j - 1, l - 1, s[j]) for j in range(l, r + 1))
        else:
            left_end = (left_block + 1) * block  # 左段末尾，一定 < r
            # 三段覆盖 [l, r] 内所有子段：左段内 / 跨过左段 / 从第一个完整块起
            across = max(range_max_xor(r, left_end + 1, s[t]) for t in range(l - 1, left_end))
            best = max(g[l], across, f[left_block + 1][r - (left_end + 1)])
        last = best
        out.append(str(best))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
