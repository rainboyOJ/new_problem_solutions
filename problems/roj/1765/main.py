#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 00:32
# update_at: 2026-10-08 00:32

import sys
from collections.abc import Iterator

MOD = 10 ** 9 + 7
LOG = 17  # 1e5 的二进制位数，倍增 LCA 的层数

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type UpTable = list[list[int]]   # up[j][v] = v 的第 2^j 级祖先，0 表示不存在
type GroupBit = list[list[int]]  # 三元差分树状数组 bit[pos] = [Σc0, Σc1, Σd]
type Trio = tuple[int, int, int]  # 某位置上的三个累计量 (Σc0, Σc1, Σd)
type Children = list[list[int]]   # child[u] = u 的孩子列表
type FibPair = tuple[int, int]    # 成对返回的斐波那契量：(Fib(t), Fib(t+1)) 或 (c0, c1)
type TreeInfo = tuple[list[int], list[int], list[int], list[int], list[int], list[int],
                      list[int], UpTable] # 八元组，各分量含义见下一行注释
# TreeInfo = (fa, tin, sz, dep, pa, pb, fib_small, up)：父亲 / 先序编号 / 子树大小 / 深度 /
#          根到各点的 ΣFib(dep)、ΣFib(dep+1) / Fib(0..n+1) / 倍增祖先表，
#          全部只依赖树的静态形状，建好之后不再改变


def fib_pair(t: int) -> FibPair:
    """返回 (Fib(t), Fib(t+1)) mod MOD，要求 t >= 0，倍增法 O(log t)。"""
    if t == 0:
        return 0, 1
    a, b = fib_pair(t >> 1)
    even = a * (2 * b - a) % MOD  # Fib(2i) = Fib(i)*(2Fib(i+1)-Fib(i))
    odd = (a * a + b * b) % MOD   # Fib(2i+1) = Fib(i)^2 + Fib(i+1)^2
    return (odd, (even + odd) % MOD) if t & 1 else (even, odd)


def fib_coef(big: int) -> FibPair:
    """更新系数 (Fib(big-1), Fib(big)) mod MOD。

    big = k - dep[X] 可能为负，用 Fib(-p) = (-1)^(p+1)*Fib(p) 延拓：
    此时两个系数正好是 ±Fib(p+1) 与 ±Fib(p)，符号由 p 的奇偶决定。
    """
    positive = abs(big)
    f, g = fib_pair(positive)  # Fib(p), Fib(p+1)
    if big >= 0:
        return (g - f) % MOD, f  # Fib(K-1) = Fib(K+1) - Fib(K)
    sign = 1 if positive & 1 else -1  # (-1)^(p+1)
    return (-sign * g) % MOD, (sign * f) % MOD


def build_static(n: int, fa: list[int], child: Children) -> TreeInfo:
    """预处理所有只与树形状有关的量：先序编号、子树大小、深度、Fib 前缀和、倍增表。

    先序编号让"子树"变成一段连续区间，这是后面差分树状数组能用起来的前提：
    一次更新只在这段区间的左右端点各记一笔，某点被多少更新覆盖就看它的前缀和。
    """
    tin = [0] * (n + 1)
    dep = [0] * (n + 1)
    order: list[int] = []
    stack = [1]
    while stack:
        u = stack.pop()
        tin[u] = len(order) + 1
        order.append(u)
        for v in child[u]:
            dep[v] = dep[u] + 1
            stack.append(v)

    sz = [1] * (n + 1)  # 子树大小：逆先序把大小并给父亲
    for u in reversed(order):
        if u != 1:
            sz[fa[u]] += sz[u]

    # fib_small[t] = Fib(t) mod MOD；深度只用到 0..n，多留一格给 Fib(dep+1)
    fib_small = [0] * (n + 2)
    fib_small[1] = 1
    for t in range(2, n + 2):
        fib_small[t] = (fib_small[t - 1] + fib_small[t - 2]) % MOD

    # pa / pb：根到 u 路径上 ΣFib(dep[v]) 与 ΣFib(dep[v]+1)，是本题两条静态权序列的前缀和
    pa = [0] * (n + 1)
    pb = [0] * (n + 1)
    for u in order:
        pa[u] = (pa[fa[u]] + fib_small[dep[u]]) % MOD
        pb[u] = (pb[fa[u]] + fib_small[dep[u] + 1]) % MOD

    # 倍增表：up[0] = fa，up[j] 由 up[j-1] 复合而来
    up: UpTable = [fa[:]]
    for _ in range(1, LOG):
        prev = up[-1]
        up.append([prev[prev[v]] for v in range(n + 1)])
    return fa, tin, sz, dep, pa, pb, fib_small, up


def bit_add(pos: int, delta: Trio, bit: GroupBit, n: int) -> None:
    """区间差分的左端点写法：从 pos 起往上累加 delta，右端点记 -delta 即自动抵消。

    不做取模：单点最多累积 m 次 MOD 级增量（1e6 × 1e9），Python 大整数完全安全，
    查询时统一取模更快。三个分量共用一个下标，所以放在同一层 while 里一起维护。
    """
    while pos <= n:
        slot = bit[pos]
        slot[0] += delta[0]
        slot[1] += delta[1]
        slot[2] += delta[2]
        pos += pos & -pos


def bit_sum(pos: int, bit: GroupBit) -> Trio:
    """位置 pos 的三元前缀和：所有子树区间覆盖了 pos 的更新累积出的 (Σc0, Σc1, Σd)。"""
    s0 = s1 = s2 = 0
    while pos > 0:
        slot = bit[pos]
        s0 += slot[0]
        s1 += slot[1]
        s2 += slot[2]
        pos -= pos & -pos
    return s0 % MOD, s1 % MOD, s2 % MOD


def lca(a: int, b: int, dep: list[int], fa: list[int], up: UpTable) -> int:
    """求 a、b 的最近公共祖先：先拉到同一深度，再同步上跳到分叉点的儿子。"""
    if dep[a] < dep[b]:
        a, b = b, a
    diff = dep[a] - dep[b]
    for j in range(LOG):
        if diff >> j & 1:
            a = up[j][a]
    if a == b:
        return a
    for j in range(LOG - 1, -1, -1):
        if up[j][a] != up[j][b]:
            a, b = up[j][a], up[j][b]
    return fa[a]


def handle_ops(tokens: Iterator[bytes], m: int, n: int, tree: TreeInfo) -> list[str]:
    """按输入顺序处理 m 个操作，返回每个询问的答案（按询问顺序）。"""
    fa, tin, sz, dep, pa, pb, fib_small, up = tree
    bit: GroupBit = [[0, 0, 0] for _ in range(n + 1)]
    out: list[str] = []

    for _ in range(m):
        op = next(tokens)
        if op == b'U':
            x, k = int(next(tokens)), int(next(tokens))
            c0, c1 = fib_coef(k - dep[x])  # Fib(K-1), Fib(K)，K = k - dep[x]
            # 差分的第三维修正项 d：把"根到 X 之上那半段"的 Fib 前缀和从 T[u] 里减掉
            d = (c0 * pa[fa[x]] + c1 * pb[fa[x]]) % MOD
            head = tin[x]        # 子树区间 [head, head+sz-1]
            tail = head + sz[x]  # 差分右端点；等于 n+1 时不会被任何前缀和查到，省掉
            bit_add(head, (c0, c1, d), bit, n)
            if tail <= n:
                bit_add(tail, (-c0, -c1, -d), bit, n)
        else:
            x, y = int(next(tokens)), int(next(tokens))
            l = lca(x, y, dep, fa, up)
            sx, sy, sl = bit_sum(tin[x], bit), bit_sum(tin[y], bit), bit_sum(tin[l], bit)
            # T[u] = 根到 u 的点权和 = Σc0·PA[u] + Σc1·PB[u] - Σd，静态前缀和乘上累计量即可
            tx = (pa[x] * sx[0] + pb[x] * sx[1] - sx[2]) % MOD
            ty = (pa[y] * sy[0] + pb[y] * sy[1] - sy[2]) % MOD
            tl = (pa[l] * sl[0] + pb[l] * sl[1] - sl[2]) % MOD
            # 点 L 在两条根链里各算了一次，把它换成点权公式（比 T[L] 只少一个 Σd 项）
            value_l = (fib_small[dep[l]] * sl[0] + fib_small[dep[l] + 1] * sl[1]) % MOD
            out.append(str((tx + ty - 2 * tl + value_l) % MOD))
    return out


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())
    n, m = int(next(tokens)), int(next(tokens))

    fa = [0] * (n + 1)  # 父亲，根的父亲是 0 号哨兵（它的 Fibonacci 前缀和都是 0）
    child: Children = [[] for _ in range(n + 1)]
    for v in range(2, n + 1):
        fa[v] = int(next(tokens))
        child[fa[v]].append(v)

    tree = build_static(n, fa, child)
    out = handle_ops(tokens, m, n, tree)

    sys.stdout.write('\n'.join(out) + ('\n' if out else ''))


if __name__ == "__main__":
    solve()
