#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 06:55
# update_at: 2026-10-08 06:55

import sys


def push_down(u: int, l: int, r: int, seg: list[int], tag: list[int]) -> None:
    """把 u 的待取反标记下传给两个儿子，各自按自己的段长取反。

    只在往儿子递归之前调用，此时必有 l < r，所以儿子编号一定在数组范围内。
    """
    if not tag[u]:
        return
    mid, left, right = (l + r) >> 1, u << 1, u << 1 | 1
    seg[left] = (mid - l + 1) - seg[left]     # 左儿子的段长是 mid-l+1
    seg[right] = (r - mid) - seg[right]       # 右儿子的段长是 r-mid
    tag[left] ^= 1
    tag[right] ^= 1
    tag[u] = 0


def modify(u: int, l: int, r: int, ql: int, qr: int, seg: list[int], tag: list[int]) -> None:
    """把 [ql, qr] 内的灯全部取反：整段被覆盖时只改本节点并打标记，否则下传后递归。"""
    if ql <= l and r <= qr:
        seg[u] = (r - l + 1) - seg[u]  # 段长 len 内有 seg[u] 盏灯亮，取反后剩 len-seg[u]
        tag[u] ^= 1                    # 两次取反互相抵消，所以是异或而不是赋值
        return
    push_down(u, l, r, seg, tag)
    mid = (l + r) >> 1
    if ql <= mid:
        modify(u << 1, l, mid, ql, qr, seg, tag)
    if qr > mid:
        modify(u << 1 | 1, mid + 1, r, ql, qr, seg, tag)
    seg[u] = seg[u << 1] + seg[u << 1 | 1]  # 回溯时用儿子的新值更新自己


def query(u: int, l: int, r: int, ql: int, qr: int, seg: list[int], tag: list[int]) -> int:
    """返回 [ql, qr] 内开着的灯数。"""
    if ql <= l and r <= qr:
        return seg[u]
    push_down(u, l, r, seg, tag)
    mid = (l + r) >> 1
    res = 0
    if ql <= mid:
        res += query(u << 1, l, mid, ql, qr, seg, tag)
    if qr > mid:
        res += query(u << 1 | 1, mid + 1, r, ql, qr, seg, tag)
    return res


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    # 灯初始全关，所以初始 sum 全是 0，不需要递归建树，只把数组开出来即可；
    # 节点 1 代表 [1, n]，节点 u 的两个儿子是 2u、2u+1，深度 O(log n) 不担心容量。
    seg = [0] * (4 * n + 5)  # seg[u] = u 这段区间内开着的灯数
    tag = [0] * (4 * n + 5)  # tag[u] = 1 表示 u 这段整体还需要取反一次

    out: list[str] = []
    for _ in range(m):
        c, a, b = next(data), next(data), next(data)
        if c == 0:
            modify(1, 1, n, a, b, seg, tag)  # 第一种操作：区间取反
        else:
            out.append(str(query(1, 1, n, a, b, seg, tag)))  # 第二种操作：输出亮灯数

    sys.stdout.write('\n'.join(out) + ('\n' if out else ''))


if __name__ == "__main__":
    solve()
