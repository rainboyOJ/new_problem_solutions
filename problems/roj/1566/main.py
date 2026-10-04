#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 18:36
# update_at: 2026-09-30 18:36

import sys

MOD = 1_000_000


def query_kth(tree: list[int], k: int, limit: int) -> int:
    """在树状数组上倍增查找第 k 小元素对应的值域离散化下标。"""
    pos, step = 0, 1 << (limit.bit_length() - 1)
    while step:
        nxt = pos + step
        if nxt <= limit and tree[nxt] < k:
            pos = nxt
            k -= tree[nxt]
        step >>= 1
    return pos + 1


def pick_best(b: int, left: int | None, right: int | None) -> int:
    """在前驱和后继中选取最接近的值，差值相等时优先选择前驱。"""
    if left is None:
        return right  # type: ignore[return-value]
    if right is None:
        return left
    return left if b - left <= right - b else right


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    events = [(next(data), next(data)) for _ in range(n)]

    coords = sorted({b for _, b in events})
    idx = {v: i + 1 for i, v in enumerate(coords)}
    m = len(coords)
    tree = [0] * (m + 1)

    def add(p: int, v: int) -> None:
        while p <= m:
            tree[p] += v
            p += p & -p

    def prefix_sum(p: int) -> int:
        total = 0
        while p:
            total += tree[p]
            p -= p & -p
        return total

    ans = 0
    pool_type: int | None = None
    pool_size = 0

    for kind, b in events:
        if pool_size == 0 or pool_type == kind:
            pool_type = kind
            add(idx[b], 1)
            pool_size += 1
            continue

        pos = idx[b]
        left_cnt = prefix_sum(pos - 1)
        left = coords[query_kth(tree, left_cnt, m) - 1] if left_cnt else None
        right = coords[query_kth(tree, left_cnt + 1, m) - 1] if left_cnt < pool_size else None

        chosen = pick_best(b, left, right)
        ans = (ans + abs(b - chosen)) % MOD
        add(idx[chosen], -1)
        pool_size -= 1

    print(ans)


if __name__ == "__main__":
    solve()
