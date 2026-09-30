#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def add(tree1: list[int], tree2: list[int], n: int, pos: int, val: int) -> None:
    """在位置 pos 累加差分增量 val，同时维护 d[i] 与 i*d[i] 的树状数组。"""
    val_weighted = pos * val
    while pos <= n:
        tree1[pos] += val
        tree2[pos] += val_weighted
        pos += pos & -pos


def prefix_sum(tree1: list[int], tree2: list[int], pos: int) -> int:
    """查询前缀 1..pos 的元素和：(pos + 1) * sum(d[i]) - sum(i * d[i])。"""
    sum_d = 0
    sum_id = 0
    i = pos
    while i > 0:
        sum_d += tree1[i]
        sum_id += tree2[i]
        i -= i & -i
    return (pos + 1) * sum_d - sum_id


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    try:
        n_token = next(data)
    except StopIteration:
        return
    n = int(n_token)
    q = int(next(data))

    tree1 = [0] * (n + 1)  # 维护差分序列 d[i]
    tree2 = [0] * (n + 1)  # 维护加权差分序列 i * d[i]

    prev = 0
    for i in range(1, n + 1):
        curr = int(next(data))
        diff = curr - prev
        add(tree1, tree2, n, i, diff)
        prev = curr

    out: list[str] = []
    for _ in range(q):
        op = next(data)
        if op == b'1':
            l = int(next(data))
            r = int(next(data))
            x = int(next(data))
            add(tree1, tree2, n, l, x)
            add(tree1, tree2, n, r + 1, -x)
        else:
            l = int(next(data))
            r = int(next(data))
            ans = prefix_sum(tree1, tree2, r) - prefix_sum(tree1, tree2, l - 1)
            out.append(str(ans))

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    solve()
