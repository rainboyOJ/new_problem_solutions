#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 18:41
# update_at: 2026-10-01 18:41

import sys

INF = 10**18  # 空子树与两个哨兵的最小值，保证永远不会成为 MIN 答案

# 用平行数组存 splay：0 号点表示空；树的中序 = [左哨兵, A1..An, 右哨兵]
ch: list[list[int]] = []     # ch[x] = [左孩子, 右孩子]
fa: list[int] = []           # 父亲
val: list[int] = []          # 节点自身的值
mn: list[int] = []           # 子树最小值
add: list[int] = []          # 子树整体加法的懒标记
rev: list[int] = []          # 子树待翻转的懒标记（push 时换左右孩子）
siz: list[int] = []          # 子树大小
cnt = 0                      # 已用节点数
root = 0
A: list[int] = []


def new_node(v: int, par: int) -> int:
    """分配一个值为 v、父亲为 par 的新节点。"""
    global cnt
    cnt += 1
    val[cnt] = mn[cnt] = v
    siz[cnt] = 1
    fa[cnt] = par
    ch[cnt] = [0, 0]
    return cnt


def pull(x: int) -> None:
    """由左右孩子重算 x 的子树大小与最小值。"""
    l, r = ch[x]
    siz[x] = siz[l] + siz[r] + 1
    mn[x] = min(val[x], mn[l], mn[r])


def pull_up(x: int) -> None:
    """从 x 往上逐层重算聚合值，直到根。"""
    while x:
        pull(x)
        x = fa[x]


def push(x: int) -> None:
    """把 x 的懒标记下传一层：整子树加 D、整子树翻转。"""
    if add[x]:
        d = add[x]
        add[x] = 0
        for s in ch[x]:
            if s:
                val[s] += d
                mn[s] += d
                add[s] += d
    if rev[x]:
        rev[x] = 0
        l, r = ch[x]
        ch[x] = [r, l]
        if l:
            rev[l] ^= 1
        if r:
            rev[r] ^= 1


def push_path(x: int) -> None:
    """把根到 x 路径上的懒标记自上而下清空。"""
    path = []
    while x:
        path.append(x)
        x = fa[x]
    for y in reversed(path):
        push(y)


def rotate(x: int) -> None:
    """把 x 上旋一层（x 及其祖先的懒标记此时都已被 push_path 清空）。"""
    y = fa[x]
    z = fa[y]
    side = ch[y][1] == x          # x 是 y 的哪一侧孩子
    w = ch[x][side ^ 1]
    if w:
        fa[w] = y
    ch[y][side] = w
    ch[x][side ^ 1] = y
    fa[y] = x
    fa[x] = z
    if z:
        ch[z][ch[z][1] == y] = x
    pull(y)


def splay_to(x: int, goal: int) -> None:
    """把 x 转成 goal 的孩子（goal=0 表示转成根），并把路径聚合值重算干净。"""
    global root
    push_path(x)
    while fa[x] != goal:
        y = fa[x]
        z = fa[y]
        if z != goal and (ch[z][1] == y) == (ch[y][1] == x):
            rotate(y)             # 一字型先转父亲，避免退化成链
        if fa[x] != goal:
            rotate(x)
    if not goal:
        root = x                  # 转到根后同步全局根指针
    pull(x)
    pull_up(fa[x])


def kth(start: int, k: int) -> int:
    """从 start 出发找中序第 k 个元素（沿途把懒标记下传）。"""
    x = start
    while True:
        push(x)
        left = siz[ch[x][0]]
        if k == left + 1:
            return x
        if k <= left:
            x = ch[x][0]
        else:
            k -= left + 1
            x = ch[x][1]


def segment(x: int, y: int) -> tuple[int, int]:
    """把 A 的区间 [x, y] 切成一颗完整子树，返回 (a, 子树根)。

    左哨兵占去树中第 1 个位置，A 的第 i 个元素在树中第 i+1 个。把
    a = 树中第 x 个（A[x-1] 或左哨兵）转到根，b = 树中第 y+2 个（A[y] 的后继）
    转成 a 的孩子，b 的左子树恰好就是整个区间。
    """
    a = kth(root, x)
    splay_to(a, 0)
    b = kth(a, y + 2)             # a 在根上用全局位置：A[y] 在 y+1，后继在 y+2
    splay_to(b, a)
    return a, ch[b][0]


def reverse_seg(x: int, y: int) -> None:
    """翻转 A 的区间 [x, y]。"""
    if x >= y:
        return
    a, key = segment(x, y)
    rev[key] ^= 1
    pull_up(a)


def revolve(x: int, y: int, t: int) -> None:
    """区间右轮换 t 次：尾部 t 个移到前面，等价于三次翻转。

    设段为 A B（A 是前 len-t 个，B 是后 t 个），目标是 B A；
    而 (A^r B^r)^r = B A，所以依次翻 A、翻 B、整段再翻。
    """
    t %= y - x + 1
    if t:
        reverse_seg(x, y - t)
        reverse_seg(y - t + 1, y)
        reverse_seg(x, y)


def build(lo: int, hi: int, par: int) -> int:
    """把 A[lo..hi] 建成尽量平衡的子树，返回子树根。"""
    if lo > hi:
        return 0
    mid = (lo + hi) >> 1
    x = new_node(A[mid], par)
    ch[x][0] = build(lo, mid - 1, x)
    ch[x][1] = build(mid + 1, hi, x)
    pull(x)
    return x


def solve() -> None:
    global root, cnt, A
    it = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    n = int(next(it))
    A = [int(next(it)) for _ in range(n)]
    m = int(next(it))

    # 容量：左右哨兵 2 个 + 原序列 n 个 + 每次 INSERT 最多新增 1 个
    cap = n + m + 5
    for arr in (ch, fa, val, mn, add, rev, siz):
        arr.extend([0] * (2 * cap))  # ch 需要成对占位，多开一倍更省心
    mn[0] = INF                      # 空节点不能把子树最小值拉成 0

    A.append(INF)                    # 右哨兵并进建树列表，保证任何后继都存在
    head = new_node(INF, 0)          # 左哨兵：树中第 1 个位置
    mid_root = build(0, n, head)     # 依次为 A1..An、右哨兵
    ch[head][1] = mid_root
    pull(head)
    root = head

    for _ in range(m):
        op = next(it)
        if op == b'ADD':
            x, y, d = int(next(it)), int(next(it)), int(next(it))
            a, key = segment(x, y)
            # 懒标记只打在子树根上：子树自身的最小值立即修正
            val[key] += d
            mn[key] += d
            add[key] += d
            pull_up(a)
        elif op == b'REVERSE':
            reverse_seg(int(next(it)), int(next(it)))
        elif op == b'REVOLVE':
            revolve(int(next(it)), int(next(it)), int(next(it)))
        elif op == b'INSERT':
            x, p = int(next(it)), int(next(it))
            a = kth(root, x + 1)     # A 的第 x 个元素
            splay_to(a, 0)
            b = kth(a, x + 2)        # 全局位置：A[x] 在 x+1，后继在 x+2（可能是右哨兵）
            splay_to(b, a)
            c = new_node(p, b)
            ch[b][0] = c             # 此刻 b 的左子树恰好为空
            pull(b)
            pull_up(a)
        elif op == b'DELETE':
            x = int(next(it))
            a = kth(root, x)         # 树中第 x 个 = A 的第 x-1 个（可能是左哨兵）
            splay_to(a, 0)
            b = kth(a, x + 2)        # 全局位置：A[x] 在 x+1，后继在 x+2
            splay_to(b, a)
            ch[b][0] = 0             # 此刻 b 的左子树恰好只有 A[x]
            pull(b)
            pull_up(a)
        else:                        # MIN
            x, y = int(next(it)), int(next(it))
            _, key = segment(x, y)
            out.append(str(mn[key]))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
