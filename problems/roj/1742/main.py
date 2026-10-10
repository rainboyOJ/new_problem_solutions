#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 20:41
# update_at: 2026-10-07 20:41

import sys

MOD = 123456789  # 题目要求的方案数模数
EMPTY = (0, 1)   # 值域空段的信息：长度 0 表示“一条都不选”，方案数恒为 1（单位元）

# 值域上的可合并信息 (最长严格上升子序列长度, 该长度下的方案数)
type Info = tuple[int, int]


def merge_info(x: Info, y: Info) -> Info:
    """合并两段值域信息：长度大者胜；等长则方案数相加；两段皆空时方案数仍为 1。"""
    (len_x, cnt_x), (len_y, cnt_y) = x, y
    if len_y > len_x:
        return y
    if len_y == len_x and len_x > 0:  # 都是空段时不能把 1 加两次
        return (len_x, (cnt_x + cnt_y) % MOD)
    return x


def prefix_best(bit_len: list[int], bit_cnt: list[int], pos: int) -> Info:
    """值域前缀 [1, pos] 的合并信息，即取值落在该前缀内的最优子序列信息。"""
    best: Info = EMPTY
    while pos > 0:
        best = merge_info(best, (bit_len[pos], bit_cnt[pos]))
        pos -= pos & -pos  # BIT 前缀拆分
    return best


def insert(bit_len: list[int], bit_cnt: list[int], pos: int, info: Info) -> None:
    """把 info 合并进值域位置 pos，维护 BIT 各节点覆盖区间的合并结果。"""
    size = len(bit_len)
    while pos < size:
        bit_len[pos], bit_cnt[pos] = merge_info((bit_len[pos], bit_cnt[pos]), info)
        pos += pos & -pos  # BIT 单点合并的影响链


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, type_ = next(data), next(data)
    resist = [next(data) for _ in range(n)]

    rank = {v: i for i, v in enumerate(sorted(set(resist)), 1)}  # 离散化：电阻值 -> rank
    k = len(rank)
    bit_len, bit_cnt = [0] * (k + 1), [1] * (k + 1)  # 初始全是空段

    for v in resist:
        r = rank[v]
        best_len, best_cnt = prefix_best(bit_len, bit_cnt, r - 1)  # 严格小于 v 的部分
        insert(bit_len, bit_cnt, r, (best_len + 1, best_cnt))      # 以 v 结尾接在最优前缀后

    ans_len, ans_cnt = prefix_best(bit_len, bit_cnt, k)  # 整个值域合并 = 全局答案
    out = [str(ans_len)]
    if type_ == 1:
        out.append(str(ans_cnt))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
