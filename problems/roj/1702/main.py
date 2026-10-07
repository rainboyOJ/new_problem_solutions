#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 16:01
# update_at: 2026-10-07 16:01

import sys

BITS = 31  # X_i, Y_j < 2^31，二进制位编号 0..30，求第 k 大时从最高位 30 开始贪心

# 可持久化 01-Trie 的节点池：三个平行列表按编号存节点，编号 0 是全局空节点
L: list[int] = [0]    # 第 0 分支（这一位为 0）的儿子编号
R: list[int] = [0]    # 第 1 分支的儿子编号
CNT: list[int] = [0]  # 子树里的元素个数


def child(idx: int, bit: int) -> int:
    """取节点 idx 的第 bit 个儿子编号（bit 为 0 走 L，为 1 走 R）。"""
    return R[idx] if bit else L[idx]


def build(y: list[int]) -> list[int]:
    """逐元素插入 y，返回 roots[j] = 只含 y[0..j-1] 的 Trie 根编号。"""
    roots = [0]
    for value in y:
        par = roots[-1]           # 上一个版本的根，也是本条链的复制来源
        root = len(CNT)           # 复制旧根开新点，新版本计数加一
        L.append(L[par])
        R.append(R[par])
        CNT.append(CNT[par] + 1)
        cur = root
        for b in range(BITS - 1, -1, -1):
            bit = value >> b & 1
            par = child(par, bit)
            nxt = len(CNT)        # 复制要下钻的旧子树
            L.append(L[par])
            R.append(R[par])
            CNT.append(CNT[par] + 1)
            if bit:
                R[cur] = nxt      # 只改下钻的那一支，另一支继续共享旧版本
            else:
                L[cur] = nxt
            cur = nxt
        roots.append(root)
    return roots


def kth(xs: list[int], roots: list[int], l: int, r: int, k: int) -> int:
    """在 i∈[u,d]、j∈[l,r] 的 A[i][j]=X[i]^Y[j] 中求第 k 大，xs 就是 X[u..d]。"""
    cur = [roots[r]] * len(xs)      # 版本 r 上每个 X[i] 各自的下钻指针
    prv = [roots[l - 1]] * len(xs)  # 版本 l-1 上的对应指针：两者相减得到区间 [l,r] 的计数
    ans = 0
    for b in range(BITS - 1, -1, -1):
        # A 的第 b 位为 1 ⟺ Y 的第 b 位等于 X 的第 b 位取反，先数出这一半的个数
        wants = [(x >> b & 1) ^ 1 for x in xs]
        cnt1 = sum(
            CNT[child(c, w)] - CNT[child(p, w)] for w, c, p in zip(wants, cur, prv)
        )
        take_high = k <= cnt1  # 第 k 大落在"当前位为 1"的那一半里
        if not take_high:
            k -= cnt1          # 跳过整半个高位区间，去低半区里找第 k 大
        ans |= take_high << b
        # 整排指针一起下钻：取高走 want 分支，取低走 want 的取反（正是 X 的这一位）
        step = [w ^ 1 if not take_high else w for w in wants]
        cur = [child(c, s) for c, s in zip(cur, step)]
        prv = [child(p, s) for p, s in zip(prv, step)]
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    X = [next(data) for _ in range(n)]
    Y = [next(data) for _ in range(m)]

    roots = build(Y)

    p = next(data)
    out: list[str] = []
    for _ in range(p):
        u, d, l, r, k = next(data), next(data), next(data), next(data), next(data)
        # X 的下标从 1 开始，X[u-1:d] 就是题面的 X[u..d]
        out.append(str(kth(X[u - 1:d], roots, l, r, k)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
