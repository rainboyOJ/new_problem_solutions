#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 12:40
# update_at: 2026-09-30 12:40

import sys


def longest_borders(s: bytes) -> list[int]:
    """KMP 失配函数：fail[i] = 前缀 s[:i] 的最长真 border（相等真前后缀）长度。"""
    fail = [0] * (len(s) + 1)
    k = 0  # 扫描到 i 时，k 恰好是 fail[i]
    for i in range(1, len(s)):
        while k and s[i] != s[k]:
            k = fail[k]  # 沿 border 链回退：次长 border 仍是 border
        if s[i] == s[k]:
            k += 1
        fail[i + 1] = k
    return fail


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    L = int(next(data))  # 题面给的字符串长度，与 len(s) 相等
    s = next(data)       # bytes：下标得到整数，字符比较更快
    fail = longest_borders(s)
    # 最短周期 = n - 最长 border，它就是能"生成"w 的最短元串长度
    print(L - fail[L])


if __name__ == "__main__":
    solve()
