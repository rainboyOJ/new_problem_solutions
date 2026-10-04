#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:28
# update_at: 2026-10-01 11:28

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n: int = next(data)
    a: list[int] = [next(data) for _ in range(n)]

    # 有序表：order 是按数值升序排好的原始下标，rank[i] 是下标 i 在表里的位置。
    order: list[int] = sorted(range(n), key=a.__getitem__)
    rank: list[int] = [0] * n
    for k, i in enumerate(order):
        rank[i] = k

    # 双向链表：在有序表上删掉一个数只改两条边，不需要搬移元素。
    prev: list[int] = list(range(-1, n - 1))  # prev[k] = k-1，-1 表示没有前驱
    nxt: list[int] = list(range(1, n + 1))    # nxt[k] = k+1
    nxt[n - 1] = -1                           # 末尾哨兵：最后一个位置没有后继

    ans: list[str] = [""] * n
    for i in range(n - 1, 0, -1):
        k = rank[i]
        # 只需比较有序表上的前驱与后继：任何更远的数，差值都不会更小。
        # 三元组按字典序比较，正好先比差值，再比 A_j 较小者，最后比下标。
        diff, value, pos = min(
            (abs(a[order[l]] - a[i]), a[order[l]], order[l])
            for l in (prev[k], nxt[k])
            if l >= 0
        )
        ans[i] = f"{diff} {pos + 1}"  # 题面要求输出 1 起始的下标

        if prev[k] >= 0:
            nxt[prev[k]] = nxt[k]  # 摘掉 i 之后，左右邻居直接相连
        if nxt[k] >= 0:
            prev[nxt[k]] = prev[k]

    # 倒序算出的答案按 (i = 2..n) 的下标顺序输出，n = 1 时没有任何一行
    sys.stdout.write('\n'.join(ans[1:]) + ('\n' if n > 1 else ''))


if __name__ == "__main__":
    solve()
