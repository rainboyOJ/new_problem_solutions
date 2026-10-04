#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:53
# update_at: 2026-10-01 11:56

import sys
from array import array

BITS = 31        # A_i < 2^31，所以要看二进制第 30 位到第 0 位
ROOT = 0         # 根结点固定编号 0
NO_CHILD = 0     # 儿子槽里的哨兵：0 表示这条边还没建出来（结点编号从 1 开始）


def build_trie(values: list[int]) -> array:
    """把所有数按二进制从高位到低位插入 Trie，返回扁平化的儿子数组。

    结点 p 的两位儿子放在 children[2p]（走 0）和 children[2p+1]（走 1）。
    每个数最多新建 BITS 个结点，所以 2*(BITS*n+1) 个 int 槽位一定够用；
    一次分配整块数组，比给三百万个结点逐个建 dict 省下大量内存。
    """
    children = array('i', [0]) * (2 * (BITS * len(values) + 1))
    top = 1                          # 下一个可用的结点编号
    for value in values:
        node = ROOT
        for shift in range(BITS - 1, -1, -1):
            slot = (node << 1) | (value >> shift & 1)   # 当前结点走这一位对应的槽
            nxt = children[slot]
            if nxt == NO_CHILD:                         # 这条边还没有，现建一个儿子
                nxt = top
                top += 1
                children[slot] = nxt
            node = nxt
    return children


def best_xor(children: array, values: list[int]) -> int:
    """每个数都在 Trie 里贪心走“相反位”，取所有数能配出的最大异或值。"""
    answer = 0
    for value in values:
        node = ROOT
        current = 0
        for shift in range(BITS - 1, -1, -1):
            bit = value >> shift & 1
            base = node << 1
            opposite = children[base | (bit ^ 1)]       # 想要异或出 1，就先找相反位那条边
            if opposite != NO_CHILD:
                current |= 1 << shift                   # 相反位存在，这一位异或结果必是 1
                node = opposite
            else:
                node = children[base | bit]             # 只能走同位，这一位异或结果是 0
        if current > answer:
            answer = current
    return answer


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    values = [next(data) for _ in range(n)]
    children = build_trie(values)
    print(best_xor(children, values))


if __name__ == "__main__":
    solve()
