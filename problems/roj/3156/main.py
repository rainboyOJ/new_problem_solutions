#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 21:34
# update_at: 2026-10-01 21:45

import sys

INF = 10 ** 9  # 不可达哨兵：答案最多 N = 25000，与真实值不会混淆


def push_min(tree: list[int], size: int, pos: int, value: int) -> None:
    """把叶子 pos 的值与 value 取 min，并向上维护区间最小值。"""
    i = size + pos
    if tree[i] <= value:
        return
    tree[i] = value
    i >>= 1
    while i:
        merged = min(tree[i << 1], tree[i << 1 | 1])
        if tree[i] == merged:  # 本节点没变，祖先自然也不会变
            break
        tree[i] = merged
        i >>= 1


def range_min(tree: list[int], size: int, left: int, right: int) -> int:
    """查询下标区间 [left, right) 的最小值。"""
    res = INF
    left += size
    right += size
    while left < right:
        if left & 1:
            res = min(res, tree[left])
            left += 1
        if right & 1:
            right -= 1
            res = min(res, tree[right])
        left >>= 1
        right >>= 1
    return res


def min_cows(left_of: dict[int, int], T: int) -> int:
    """返回铺满班次 1..T 的最少奶牛数，不可达时返回 INF。

    left_of[r] 是所有右端点为 r 的牛里最小的左端点。按右端点升序处理，
    一头牛 [l, r] 能接在任意一个"已铺满到 p"的方案后面（p >= l-1，重叠合法），
    所以每次只需查一次 dp[l-1 .. min(r,T)] 的最小值，再更新 dp[min(r,T)]。
    """
    size = 1
    while size < T + 2:  # dp 下标是 0..T，加 2 保证叶子数够用且是 2 的幂
        size <<= 1
    tree = [INF] * (size << 1)
    push_min(tree, size, 0, 0)  # dp[0] = 0：还没铺任何班次

    for right, left in sorted(left_of.items()):
        covered = min(right, T)  # 覆盖到 T 之后再多的班次没有意义
        prev = range_min(tree, size, left - 1, covered + 1)
        if prev < INF:  # 前面那段铺不满，这头牛接不上任何方案
            push_min(tree, size, covered, prev + 1)

    return range_min(tree, size, T, T + 1)  # 答案就是 dp[T]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, T = next(data), next(data)

    # 右端点相同的牛只留左端点最靠左的那头，其余都被它完全支配
    left_of: dict[int, int] = {}
    for _ in range(n):
        left, right = next(data), next(data)
        if left <= T:  # 一个班次都盖不到的牛直接丢弃
            left_of[right] = min(left_of.get(right, T + 1), left)

    ans = min_cows(left_of, T)
    print(ans if ans < INF else -1)


if __name__ == "__main__":
    solve()
