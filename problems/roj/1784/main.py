#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 02:26
# update_at: 2026-10-08 02:26

import sys
from functools import cache
from itertools import accumulate
from collections.abc import Iterator

MOD = 998244353
MAX_CELLS = 32                    # 格子数上限 4*7 = 28，阶乘表开到 32!
X_BYTE = ord('X')                 # 网格按 bytes 读入，下标取出来的就是它的字节值

# 阶乘与阶乘逆元：g(T) 的转移里要算 a!/b!，一次预处理到 32!
FACT = list(accumulate(range(1, MAX_CELLS + 1), lambda acc, i: acc * i % MOD, initial=1))
INVFACT = [pow(f, MOD - 2, MOD) for f in FACT]

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Mask = int                    # 格子集合掩码：第 v 位为 1 表示格子 v 属于该集合
type Adj = tuple[int, ...]         # adj[v] = 与格子 v 八连通的格子集合（掩码）
type Grid = list[bytes]            # 一组数据的 n 行网格，每行是等长 bytes
type Frame = tuple[int, int, Mask]  # 迭代式枚举的栈帧：候选下标 / 已选掩码 / 被禁掩码


@cache
def adj_of(n: int, m: int) -> Adj:
    """八连通邻接掩码：adj[v] 的第 u 位为 1 表示格子 v 与 u 八连通（含斜向 4 方向）。"""
    return tuple(
        sum(1 << ((i + di) * m + j + dj)
            for di in (-1, 0, 1) for dj in (-1, 0, 1)
            if (di or dj) and 0 <= i + di < n and 0 <= j + dj < m)
        for i in range(n) for j in range(m)
    )


def extras_of(cands: list[int], adj: Adj, cmask: Mask) -> Iterator[Mask]:
    """产出候选格里所有两两不八连通的子集：逐个候选格做“选 / 不选”的决定。

    选了一个格子就把它在候选集内的邻居禁掉，所以产出的每个掩码都能与 X 拼成独立集。
    """
    stack: list[Frame] = [(0, 0, 0)]
    while stack:
        pos, chosen, banned = stack.pop()
        if pos == len(cands):                    # 每个候选格都做完决定，得到一个合法后缀
            yield chosen
            continue
        stack.append((pos + 1, chosen, banned))  # 不选这个候选格
        c = cands[pos]
        if not banned >> c & 1:                  # 没被已选格封掉才允许选
            stack.append((pos + 1, chosen | 1 << c, banned | (adj[c] & cmask)))


def ways_all_valleys(T: Mask, N: int, adj: Adj) -> int:
    """g(T)：只要求集合 T 中每一格都是山谷（T 必须是八连通独立集）的填数方案数。

    把 T 的内部先后顺序固定成 (t_1..t_k)，再把 T 之外的格子插进去：格子 u 必须排在它
    在 T 里最后一个邻居之后。按“最后一个邻居的位置”从大到小插入时，插第 j 个的可选
    位置数是 k-h(u)+j，于是对全部顺序求和就变成前缀集合上的子集 DP：dp[Y] = 山谷先后
    顺序的前缀恰为 Y（|Y| = h）时，已插入格子产生的系数和；在 T 中没有任何邻居的
    freeCnt 个格子另行连乘 N!/(N-freeCnt)!。
    """
    members = [v for v in range(N) if T >> v & 1]  # 压缩 T 中格子的下标，掩码宽度降到 k
    k = len(members)
    size = 1 << k
    rank = [0] * N                               # rank[v] 是格子 v 在 T 中的压缩下标
    for i, v in enumerate(members):
        rank[v] = i
    celCnt = [0] * size                          # celCnt[Y] = T 中邻居全落在 Y 内的非 T 格数
    for u in range(N):
        if T >> u & 1:
            continue
        sub, nb = 0, adj[u] & T
        while nb:
            low = nb & -nb
            nb ^= low
            sub |= 1 << rank[low.bit_length() - 1]
        celCnt[sub] += 1
    for b in range(k):                           # 子集和（zeta）变换：celCnt[Y] 变成前缀计数
        step, block = 1 << b, 2 << b
        for base in range(0, size, block):
            for Y in range(base + step, base + block):
                celCnt[Y] += celCnt[Y - step]
    freeCnt = celCnt[0]
    dp = [0] * size
    dp[0] = 1
    for Y in range(size):
        cur = dp[Y]
        if not cur:
            continue
        head = (size - 1) ^ Y                    # 还没排进山谷内部顺序的格子
        h = Y.bit_count()
        a = N - h - 1 - celCnt[Y]                # 相邻两个前缀之间补入的格子数是 a!/b!
        base = N - h - 1
        fa = FACT[a] * cur % MOD
        while head:
            low = head & -head
            head ^= low
            nxtY = Y | low
            dp[nxtY] = (dp[nxtY] + fa * INVFACT[base - celCnt[nxtY]]) % MOD
    return dp[size - 1] * FACT[N] % MOD * INVFACT[N - freeCnt] % MOD


def answer_of(n: int, m: int, rows: Grid) -> int:
    """一组数据的答案：X 非独立直接 0，否则对所有含 X 的独立超集做容斥求和。"""
    N = n * m
    adj = adj_of(n, m)
    xmask = sum(1 << (i * m + j)
                for i in range(n) for j in range(m) if rows[i][j] == X_BYTE)
    # 山谷集合不可能为空：全局最小值那一格必是山谷（无邻居时也恒为山谷，N=1 答案为 1）；
    # X 内部八连通相邻时两个“自己最小”的约束互相矛盾，答案为 0。
    x_adjacent = any(xmask >> v & 1 and adj[v] & xmask for v in range(N))
    if xmask == 0 or x_adjacent:
        return 0
    cands = [v for v in range(N) if not xmask >> v & 1 and not adj[v] & xmask]
    cmask = sum(1 << v for v in cands)
    ans = 0
    for extra in extras_of(cands, adj, cmask):
        ways = ways_all_valleys(xmask | extra, N, adj)
        sign = -1 if extra.bit_count() & 1 else 1   # 容斥系数 (-1)^(|T|-|X|)
        ans += sign * ways
    return ans % MOD


def groups_of(tokens: Iterator[bytes]) -> Iterator[tuple[int, int, Grid]]:
    """把 token 流按“n m + 后续 n 行网格”分组（组数不固定，读到 EOF 为止）。"""
    for first in tokens:
        n, m = int(first), int(next(tokens))
        yield n, m, [next(tokens) for _ in range(n)]


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())
    out = [str(answer_of(n, m, rows)) for n, m, rows in groups_of(tokens)]
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
