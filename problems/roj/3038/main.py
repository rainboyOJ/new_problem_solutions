#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:39
# update_at: 2026-10-01 11:39

import sys

MOD = (1 << 61) - 1  # 梅森素数 2^61 - 1，模它时哈希值均匀，冲突概率可忽略
BASE = 131           # 哈希进制：字母集是 26 个小写字母，取比字符集大的底数


def prefix_hashes(s: str) -> tuple[list[int], list[int]]:
    """返回 (h, p)：h[i] 是前缀 s[:i] 的哈希值，p[i] 是 BASE^i mod MOD。"""
    h = [0] * (len(s) + 1)  # h[0] = 0，空串哈希
    p = [1] * (len(s) + 1)  # p[0] = 1，BASE^0
    for i, code in enumerate(map(ord, s), 1):
        h[i] = (h[i - 1] * BASE + code) % MOD
        p[i] = p[i - 1] * BASE % MOD
    return h, p


def sub_hash(h: list[int], p: list[int], l: int, r: int) -> int:
    """取出区间 [l, r] 的哈希值：去掉前缀 [1, l-1] 贡献的高位。"""
    return (h[r] - h[l - 1] * p[r - l + 1]) % MOD


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    s = tokens[0].decode()
    query_count = int(tokens[1])

    h, p = prefix_hashes(s)

    # 4m 个数字依次取 4 个就是一组 (l1, r1, l2, r2)，zip 能对齐同一个迭代器
    it = map(int, tokens[2:])
    out = [
        'Yes' if sub_hash(h, p, l1, r1) == sub_hash(h, p, l2, r2) else 'No'
        for l1, r1, l2, r2 in zip(it, it, it, it)
    ]
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
