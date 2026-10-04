#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 07:26
# update_at: 2026-10-01 07:26

import sys


def extend(bits: int, v: int, q: int) -> int:
    """在位集 bits 上并入“再倒任意整数桶 v”的效果：与 v 的倍数做加法闭包。

    倍增：依次左移 v、2v、4v…并或回去，恰好补齐所有倍数增量；
    超过 q 的位直接截掉（之后只会加正数，不会再用到它们）。
    """
    full = (1 << (q + 1)) - 1
    step = v
    while step <= q:
        bits |= (bits << step) & full
        step <<= 1
    return bits


def pick(q: int, buckets: list[int], start: int, rest: int, total: int, bits: int) -> list[int] | None:
    """按字典序在升序 buckets[start:] 里再选 rest 个桶，成功返回所选桶，失败返回 None。

    bits 是已选桶能刚好量出的夸脱位集（0..q），total 是已选容积之和。
    桶按升序逐个倒，每个选中的桶至少倒一次 → total+v > q 时后面的桶更大，
    整条分支的剩余桶全部装不下，直接 break（这也是字典序扫描的天然截断）。
    """
    if rest == 0:
        return [] if bits >> q & 1 else None
    for i in range(start, len(buckets) - rest + 1):  # 剩余桶必须够 rest 个
        v = buckets[i]
        if total + v > q:
            break
        tail = pick(q, buckets, i + 1, rest - 1, total + v, extend(bits, v, q))
        if tail is not None:
            return [v] + tail
    return None


def best_set(q: int, buckets: list[int]) -> list[int]:
    """桶数从 1 往上枚举：更少桶必更优；同数量下 dfs 天然按升序字典序，首个成功即答案。"""
    for k in range(1, len(buckets) + 1):
        chosen = pick(q, buckets, 0, k, 0, 1)  # bits 初始只有 0 夸脱可达
        if chosen is not None:
            return chosen
    raise AssertionError("题目保证有解")  # 兜底，正常数据不会走到


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    q = next(data)
    p = next(data)
    buckets = sorted({next(data) for _ in range(p)})  # 去重：重复容积不改变可达集合
    ans = best_set(q, buckets)
    print(' '.join(map(str, [len(ans)] + ans)))


if __name__ == "__main__":
    solve()
