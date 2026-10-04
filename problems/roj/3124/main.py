#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 18:30
# update_at: 2026-10-01 18:30

import sys

NONE = -1      # 延迟标记：-1 无标记，0 整段清空，1 整段入住
OCCUPY, CLEAR = 1, 0  # 与延迟标记同义的业务含义，避免在调用点裸写 1 / 0

length: list[int] = []  # 每个节点覆盖的房间数
pre: list[int] = []     # 该段从左端起的最长连续空房数
suf: list[int] = []     # 该段从右端起的最长连续空房数
best: list[int] = []    # 该段内部的最长连续空房数
lazy: list[int] = []    # 延迟标记，含义见 NONE


def prepare(n: int) -> int:
    """建树：叶子记区间长度（超出 n 的补 0），初始全部空房，标记清空；返回叶子数 M。

    线段树按 [1, M] 的坐标递归，M 是大于等于 n 的最小 2 的幂；补出来的 M - n
    个假房间长度为 0，永远不可能被选中，却让左右孩子的分界点保持整齐。
    """
    global length, pre, suf, best, lazy
    M = 1 << (n - 1).bit_length()        # 叶子数，同时就是房间坐标的上界
    size = M << 1
    length = [1 if 1 <= i - M + 1 <= n else 0 for i in range(size)]
    for i in range(M - 1, 0, -1):        # 自底向上累加出每个节点的区间长度
        length[i] = length[i << 1] + length[i << 1 | 1]
    pre, suf, best = length.copy(), length.copy(), length.copy()
    lazy = [NONE] * size
    return M


def apply(node: int, color: int) -> None:
    """把 node 整段刷成 color：入住则空房归零，清空则整段都是空房。"""
    empty = 0 if color == OCCUPY else length[node]
    pre[node] = suf[node] = best[node] = empty
    lazy[node] = color


def push(node: int) -> None:
    """把 node 的延迟标记下传给孩子，并清掉自己的标记。"""
    tag = lazy[node]
    if tag != NONE:
        apply(node << 1, tag)
        apply(node << 1 | 1, tag)
        lazy[node] = NONE


def pull(node: int) -> None:
    """由两个孩子重算 node 的三个空房统计量。"""
    left, right = node << 1, node << 1 | 1
    # 左孩子整段全空时，前缀才能越过它继续接上右孩子的前缀
    pre[node] = pre[left] + (pre[right] if pre[left] == length[left] else 0)
    suf[node] = suf[right] + (suf[left] if suf[right] == length[right] else 0)
    best[node] = max(best[left], best[right], suf[left] + pre[right])


def modify(node: int, l: int, r: int, ql: int, qr: int, color: int) -> None:
    """把房间区间 [ql, qr] 整段刷成 color。"""
    if ql <= l and r <= qr:              # 当前段被完全覆盖，整段打标记
        apply(node, color)
        return
    push(node)
    mid = (l + r) >> 1
    if ql <= mid:
        modify(node << 1, l, mid, ql, qr, color)
    if qr > mid:
        modify(node << 1 | 1, mid + 1, r, ql, qr, color)
    pull(node)


def query(node: int, l: int, r: int, d: int) -> int:
    """找最靠左的、能装下 d 个连续空房的起点房间号；装不下返回 0。"""
    if best[node] < d:                   # 本段最长空房都不够，整段无解
        return 0
    if l == r:
        return l                         # 走到叶子说明 d 必为 1，就是这一间
    push(node)
    mid = (l + r) >> 1
    left, right = node << 1, node << 1 | 1
    if best[left] >= d:                  # 优先最左：左孩子内部就能装下
        return query(left, l, mid, d)
    if suf[left] + pre[right] >= d:      # 其次：正好跨在左右孩子交界处
        return mid - suf[left] + 1
    return query(right, mid + 1, r, d)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    M = prepare(n)

    out: list[str] = []
    for _ in range(m):
        op = next(data)
        if op == 1:
            d = next(data)
            start = query(1, 1, M, d)
            out.append(str(start))
            if start:                    # 找到才真的入住，找不到就只是报 0
                modify(1, 1, M, start, start + d - 1, OCCUPY)
        else:
            x, d = next(data), next(data)
            modify(1, 1, M, x, x + d - 1, CLEAR)

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
