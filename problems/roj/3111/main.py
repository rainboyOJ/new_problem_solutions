#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 17:40
# update_at: 2026-10-01 17:40

import sys


def kth_free(tree: list[int], k: int, log: int) -> int:
    """树状数组上倍增：返回剩余（未被占用）身高中第 k 小的下标（1-based）。"""
    pos = 0
    for step in (1 << p for p in range(log, -1, -1)):
        nxt = pos + step
        if nxt < len(tree) and tree[nxt] < k:  # 前缀和不够 k，说明第 k 小还在更右边
            pos, k = nxt, k - tree[nxt]
    return pos + 1


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [0, 0]  # a[0] 占位；a[1] = 0（第 1 头牛前面没有牛，未读入）
    for _ in range(n - 1):
        a.append(next(data))  # a[i]（i≥2）：第 i 头牛前面比它矮的数量

    tree = [0] * (n + 1)
    for i in range(1, n + 1):
        tree[i] = i & -i  # 初值即建树：所有身高都空闲，前缀 [1..i] 恰有 i 个空闲

    log = n.bit_length()  # 倍增跳的最大步长 2^log 覆盖 n
    ans: list[int] = []
    for i in range(n, 0, -1):
        # 从后往前确定：第 i 头牛的身高是剩余身高里第 a[i]+1 小的
        h = kth_free(tree, a[i] + 1, log)
        ans.append(h)
        p = h
        while p <= n:  # 树状数组单点 -1：身高 h 已被占用
            tree[p] -= 1
            p += p & -p

    print('\n'.join(map(str, reversed(ans))))


if __name__ == "__main__":
    solve()
