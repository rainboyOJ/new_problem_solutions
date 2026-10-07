#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 23:10
# update_at: 2026-10-07 23:45

import sys
from collections import Counter
from collections.abc import Iterable

MAXC = 100000          # 颜色上界（题面 1 ≤ n ≤ 100000，颜色取值 1..n）
OCT = MAXC // 8 + 1    # 颜色位集的字节宽度：定宽才能反复用 int.from_bytes 拼同一个整数
BLK = 64               # 位置（DFS 序）分块大小：块内暴力扫，块间用线段树并

# 类型别名：这些复合类型在签名/声明里出现 ≥2 次，含义只在这里解释一遍
type Ints = list[int]                       # 一串整数：顶点编号 / 颜色表 / 位集线段树
type Bits = int                             # 颜色位集：二进制第 c 位为 1 表示颜色 c 出现过
type Edges = Ints                           # 边表：按 u, v 成对存放的 2(n-1) 个顶点编号
type Counts = dict[tuple[int, int], int]    # (颜色, 位置块) -> 出现次数

# 模块级状态：build_index 里一次建好，query / modify 只读改，不再层层传参
N = 0                  # 点数
P = 0                  # 线段树叶子偏移（≥ 位置块数的 2 的幂）
TIN: Ints = []         # 顶点的 DFS 入时间（1 基）
TOUT: Ints = []        # 顶点子树内最大的入时间：子树 u 即位置区间 [TIN[u]-1, TOUT[u]-1]
ORDER: Ints = []       # ORDER[k] 是 DFS 序第 k 个位置（0 基）上的顶点
CLR: Ints = []         # 每个顶点当前的颜色
SEG: Ints = []         # 颜色位集线段树：叶在 SEG[P..P+nb-1]，节点是两子节点位集的或
CNT: Counts = {}       # 清位前必须先查它，否则会把还出现着的颜色误当成消失


def dfs_order(n: int, edges: Edges) -> tuple[Ints, Ints, Ints]:
    """按 DFS 序重排：返回 (入时间, 子树最大入时间, 每个位置上的顶点)。

    显式开栈迭代深搜，避免 n = 1e5 的链把递归栈压爆；
    已进过栈的儿子不会再进，所以唯一的重复邻居就是父亲。
    """
    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for i in range(0, 2 * (n - 1), 2):
        u, v = edges[i], edges[i + 1]
        adj[u].append(v)
        adj[v].append(u)
    tin = [0] * (n + 1)
    tout = [0] * (n + 1)
    order = [0] * n
    par = [0] * (n + 1)    # 父节点，用来跳过回边
    nxt = [0] * (n + 1)    # 每个顶点下一条待访问的边（邻接表下标）
    par[1] = -1
    tin[1] = 1
    order[0] = 1
    timer = 1
    stack = [1]
    while stack:
        u = stack[-1]
        if nxt[u] == len(adj[u]):   # 儿子都进过栈了，子树区间在此闭合
            tout[u] = timer
            stack.pop()
            continue
        v = adj[u][nxt[u]]
        nxt[u] += 1
        if v == par[u]:
            continue
        par[v] = u
        timer += 1
        tin[v] = timer
        order[timer - 1] = v
        stack.append(v)
    return tin, tout, order


def bits_of(cols: Iterable[int]) -> Bits:
    """把一串颜色压成颜色位集（位编号的约定见 type Bits）。"""
    buf = bytearray(OCT)   # 定宽缓冲：所有位集字节数一致，才能直接按位或
    for c in cols:
        buf[c >> 3] |= 1 << (c & 7)
    return int.from_bytes(buf, 'little')


def seg_tree(leaves: Ints) -> tuple[int, Ints]:
    """把每个位置块的颜色位集摆成线段树叶子：返回 (叶子偏移 P, 整棵树)。

    叶子数补齐到 2 的幂 P，非叶节点是两个儿子位集的或，
    于是任意一段完整块都能用 O(log) 个节点并出来。
    """
    p = 1 << (len(leaves) - 1).bit_length()
    seg = [0] * p + leaves + [0] * (p - len(leaves))
    for i in range(p - 1, 0, -1):
        seg[i] = seg[2 * i] | seg[2 * i + 1]
    return p, seg


def build_index(n: int, clr: Ints, edges: Edges) -> None:
    """预处理好全套索引：DFS 序、每个位置块的位集、块位集线段树、(颜色, 块) 计数。"""
    global N, P, TIN, TOUT, ORDER, CLR, CNT, SEG
    N = n
    CLR = clr
    TIN, TOUT, ORDER = dfs_order(n, edges)
    blocks = [ORDER[i:i + BLK] for i in range(0, n, BLK)]   # 位置分块后的每一块
    P, SEG = seg_tree([bits_of(CLR[v] for v in blk) for blk in blocks])
    # 位集只能置位/清位，靠这张表才能判断某一位该不该清
    CNT = Counter((CLR[v], k // BLK) for k, v in enumerate(ORDER))


def block_range(fL: int, fR: int) -> Bits:
    """位置块区间 [fL, fR] 的并集颜色位集：线段树自底向上取 O(log) 个节点。"""
    seg = SEG          # 绑到局部：循环里每层都要取一次全局名，绑一次就够了
    i = fL + P
    j = fR + P
    acc = 0
    while i <= j:
        if i & 1:          # i 是父节点的右儿子：它完全落在区间里，取走自己再右移
            acc |= seg[i]
            i += 1
        if not j & 1:      # j 是父节点的左儿子：同理取走
            acc |= seg[j]
            j -= 1
        i >>= 1            # i-1、j+1 已经取走，剩下的是上一层的一对邻区间
        j >>= 1
    return acc


def repaint(b: int) -> None:
    """位置块 b 的位集变了：自叶向根重算它到根这条链上的 O(log) 个祖先。"""
    seg = SEG
    i = (P + b) >> 1
    while i:
        seg[i] = seg[2 * i] | seg[2 * i + 1]
        i >>= 1


def query(u: int, l: int, r: int) -> int:
    """子树 u 里颜色落在 [l, r] 的颜色种数。

    区间 = 头部残缺块 + 中间完整块（线段树并成一个位集）+ 尾部残缺块；
    三部分并成同一个颜色位集，最后按 [l, r] 截取并数一次二进制里的 1。
    """
    l = max(l, 1)   # 强制在线解码可能把 l, r 送出界，夹回 [1, n]
    r = min(r, N)
    if l > r:
        return 0
    lo = TIN[u] - 1
    hi = TOUT[u] - 1
    span = ((1 << (r - l + 1)) - 1) << l      # 只留颜色区间 [l, r] 的位，其余位置 0
    fL = -(-lo // BLK)                        # 完整落在区间内的第一个位置块
    fR = (hi + 1) // BLK - 1                  # 完整落在区间内的最后一个位置块
    if fL > fR:                               # 没有完整块：整段落在至多两个残缺块里
        return (bits_of(CLR[v] for v in ORDER[lo:hi + 1]) & span).bit_count()
    mask = block_range(fL, fR)
    head_hi = fL * BLK - 1                    # 头部残缺部分：第 fL-1 块的尾巴
    if lo <= head_hi:
        mask |= bits_of(CLR[v] for v in ORDER[lo:head_hi + 1])
    tail_lo = (fR + 1) * BLK                  # 尾部残缺部分：第 fR+1 块的脑袋
    if tail_lo <= hi:
        mask |= bits_of(CLR[v] for v in ORDER[tail_lo:hi + 1])
    return (mask & span).bit_count()


def modify(u: int, cnew: int) -> None:
    """把顶点 u 的颜色改成 cnew，同步块内计数、块位集与线段树。"""
    old = CLR[u]
    if old == cnew:
        return
    CLR[u] = cnew
    b = (TIN[u] - 1) // BLK
    leaf = P + b
    gone = (old, b)
    left = CNT[gone] - 1        # 旧颜色在这个块里还剩几次
    CNT[gone] = left
    born = (cnew, b)
    seen = CNT.get(born, 0)     # 新颜色在这个块里原有的出现次数
    CNT[born] = seen + 1
    # 位集只在「旧颜色清零」或「新颜色首现」时才变，两个改动合并成一次祖先重算
    if left == 0:
        SEG[leaf] &= ~(1 << old)
    if seen == 0:
        SEG[leaf] |= 1 << cnew
    if left == 0 or seen == 0:
        repaint(b)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, q, t = next(data), next(data), next(data)
    clr = [0] + [next(data) for _ in range(n)]     # 顶点 1..n 的初始颜色，0 号位留空
    edge_ints = 2 * (n - 1)                        # 边表占的整数个数
    edges: Edges = [next(data) for _ in range(edge_ints)]

    build_index(n, clr, edges)

    out: Ints = []
    lastans = 0
    for _ in range(q):
        op = next(data)
        if op == 1:
            u, l, r = next(data), next(data), next(data)
            if t:                                     # t=1：除操作类型外全都要异或
                u, l, r = u ^ lastans, l ^ lastans, r ^ lastans
            lastans = query(u, l, r)
            out.append(str(lastans))
        else:
            u, c = next(data), next(data)
            if t:
                u, c = u ^ lastans, c ^ lastans
            modify(u, c)
    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
