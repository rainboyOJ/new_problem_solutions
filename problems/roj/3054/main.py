#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 12:29
# update_at: 2026-10-01 12:29

import sys

DELIM = ord('z') + 1  # 分隔符：大于所有小写字母，保证匹配不会越过 B 的结尾（长度恒不超过 M）


def z_function(seq: bytes) -> list[int]:
    """Z 函数：z[i] 是 seq 与 seq[i:] 的最长公共前缀长度，均摊 O(|seq|)。"""
    z = [0] * len(seq)
    left = right = 0  # 目前右端最靠后的匹配段 [left, right)
    for i in range(1, len(seq)):
        if i < right:
            z[i] = min(right - i, z[i - left])  # 借用左端对称位置的答案，再截断到已知段的右端
        while i + z[i] < len(seq) and seq[z[i]] == seq[i + z[i]]:
            z[i] += 1
        if i + z[i] > right:
            left, right = i, i + z[i]
    return z


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    m = int(next(data))
    q = int(next(data))
    a = next(data)
    b = next(data)
    queries = [int(next(data)) for _ in range(q)]

    # 拼成 B + 分隔符 + A，一次 Z 函数就同时给出 A 每个后缀与 B 的匹配长度
    z = z_function(b + bytes((DELIM,)) + a)[m + 1:]

    hit = [0] * (m + 1)  # hit[length] = 匹配长度恰好为 length 的后缀个数
    for length in z:
        hit[length] += 1

    ans = [hit[t] if t <= m else 0 for t in queries]  # 匹配长度不会超过 M
    print('\n'.join(map(str, ans)))


if __name__ == "__main__":
    solve()
