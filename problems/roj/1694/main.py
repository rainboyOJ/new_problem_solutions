#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:45
# update_at: 2026-10-07 15:50

import sys
from itertools import accumulate

MASK = (1 << 64) - 1   # 滚动哈希按 2^64 自然溢出：乘法后取低 64 位
BASE = 1315423911      # 哈希基数，取一个大奇数，与 main.cpp 的底数一致

# 类型别名：Manacher 返回 (d1, d2)，build_hash 返回 (前缀哈希, 幂表)，都是这个形状
type TwoTables = tuple[list[int], list[int]]
# Prep 打包一组询问要用到的全部预处理表，字段依次是：
# (|A|, |B|, fA 前缀和, (cntB+1) 前缀和, A 哈希表, rev(B) 哈希表, BASE 幂表)
type Prep = tuple[int, int, list[int], list[int], list[int], list[int], list[int]]


def manacher(s: bytes) -> TwoTables:
    """返回 (d1, d2)：d1[i] 是以 i 为中心的最长奇回文半径，d2[i] 是以 i-1、i 为中心的最长偶回文半径。"""
    size = len(s)
    d1 = [0] * size
    left, right = 0, -1
    for i in range(size):
        k = 1 if i > right else min(d1[left + right - i], right - i + 1)
        while i - k >= 0 and i + k < size and s[i - k] == s[i + k]:
            k += 1
        d1[i] = k
        if i + k - 1 > right:
            left, right = i - k + 1, i + k - 1

    d2 = [0] * size
    left, right = 0, -1
    for i in range(size):
        k = 0 if i > right else min(d2[left + right - i + 1], right - i + 1)
        while i - k - 1 >= 0 and i + k < size and s[i - k - 1] == s[i + k]:
            k += 1
        d2[i] = k
        if i + k - 1 > right:
            left, right = i - k, i + k - 1
    return d1, d2


def prefix_pal_counts(s: bytes) -> list[int]:
    """counts[i] = s[i:] 的非空回文前缀个数（1-based 下标，末尾补一个 0）。"""
    size = len(s)
    d1, d2 = manacher(s)
    diff = [0] * (size + 2)
    for i in range(size):
        # 奇回文 s[i-k+1..i+k-1] 的起点落在 [i-d1[i]+1, i]
        diff[i - d1[i] + 1] += 1
        diff[i + 1] -= 1
        if d2[i]:
            # 偶回文 s[i-k..i+k-1] 的起点落在 [i-d2[i], i-1]
            diff[i - d2[i]] += 1
            diff[i] -= 1
    counts = [0] * (size + 2)   # 每个回文子串只给它的起点记一次，差分摊平后取前缀和
    cur = 0
    for i in range(size):
        cur += diff[i]
        counts[i + 1] = cur
    return counts


def suffix_pal_counts(s: bytes) -> list[int]:
    """counts[e] = s[:e] 的非空回文后缀个数（e = 0..len(s)）。"""
    size = len(s)
    d1, d2 = manacher(s)
    diff = [0] * (size + 2)
    for i in range(size):
        # 奇回文的结束位置落在 [i+1, i+d1[i]]，偶回文落在 [i+1, i+d2[i]]
        diff[i + 1] += 1
        diff[i + d1[i] + 1] -= 1
        if d2[i]:
            diff[i + 1] += 1
            diff[i + d2[i] + 1] -= 1
    counts = [0] * (size + 1)
    cur = 0
    for e in range(1, size + 1):
        cur += diff[e]
        counts[e] = cur
    return counts


def build_hash(s: bytes) -> TwoTables:
    """返回 s 的前缀哈希表与 BASE 的幂表。"""
    size = len(s)
    h = [0] * (size + 1)
    for i, ch in enumerate(s):
        h[i + 1] = (h[i] * BASE + ch) & MASK
    power = [1] * (size + 1)
    for i in range(1, size + 1):
        power[i] = power[i - 1] * BASE & MASK
    return h, power


def prepare(a: bytes, b: bytes) -> Prep:
    """预处理两串：回文计数的前缀和表，加上 A 与 rev(B) 的滚动哈希表。"""
    rev_b = b[::-1]   # B_y 的匹配方向就是 B 的逆序
    # accumulate(prefix_pal_counts(a)) 即 fA 的前缀和，恰好多留一格支持 x+P = n+1
    pre_f = list(accumulate(prefix_pal_counts(a)))
    # 每个匹配长度 e 都额外贡献一种"中间段为空"的取法，所以计数是 cntB[e]+1
    pre_e = list(accumulate((c + 1 for c in suffix_pal_counts(b)), initial=0))
    hash_a, power = build_hash(a)
    hash_r, _ = build_hash(rev_b)
    return len(a), len(b), pre_f, pre_e, hash_a, hash_r, power


def longest_common_prefix(hash_a: list[int], hash_r: list[int], power: list[int],
                          st: int, yst: int, limit: int) -> int:
    """二分求 A[st..] 与 rev(B)[yst..] 的最长公共前缀长度，长度上限为 limit。"""
    lo, hi = 0, limit
    while lo < hi:
        mid = (lo + hi + 1) >> 1
        # 两串各取 mid 个字符的区间哈希，相等就认为这 mid 个字符匹配
        left = (hash_a[st + mid] - hash_a[st] * power[mid]) & MASK
        right = (hash_r[yst + mid] - hash_r[yst] * power[mid]) & MASK
        if left == right:
            lo = mid
        else:
            hi = mid - 1
    return lo


def count_pairs(prep: Prep, x: int, y: int) -> int:
    """回答一组询问：F(A_x, B_y) 的值。"""
    n, m, pre_f, pre_e, hash_a, hash_r, power = prep
    st = x - 1                       # A_x 在 A 中的起点（0-based）
    length = m - y + 1               # B_y 的长度
    common = longest_common_prefix(hash_a, hash_r, power, st, y - 1, min(n - st, length))
    # |S| <= |T| 的 p = 1..common 段 + |S| > |T| 的 q = 1..common 段
    return (pre_e[length] - pre_e[length - common]) + (pre_f[x + common] - pre_f[x])


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    dtype = next(data)   # 第一行是数据类型，三档数据共用同一套算法，只做占位
    prep = prepare(next(data), next(data))

    q = int(next(data))
    out: list[str] = []
    for _ in range(q):
        x = int(next(data))
        y = int(next(data))
        out.append(str(count_pairs(prep, x, y)))
    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
