#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 11:53
# update_at: 2026-09-30 12:01

import sys


def prefix_function(pattern: bytes) -> list[int]:
    """pi[i] = pattern 的前 i 个字符里，最长的"既是真前缀又是真后缀"的长度。"""
    n = len(pattern)
    pi = [0] * (n + 1)
    for i in range(1, n):
        j = pi[i]                                 # 先继承上一个位置的最长 border
        while j and pattern[i] != pattern[j]:     # 失配就沿 border 链回退
            j = pi[j]
        if pattern[i] == pattern[j]:
            j += 1
        pi[i + 1] = j
    return pi


def border_chain(pi: list[int]) -> list[str]:
    """从链尾回溯得到全部 border 长度（含整串），升序返回。"""
    lengths: list[str] = []
    j = len(pi) - 1                               # 整串本身一定是一个 border
    while j:                                      # 跳到 0 说明链走完，空串不算 border
        lengths.append(str(j))
        j = pi[j]
    return lengths[::-1]                          # 回溯是降序的，翻转成题目要求的递增


def solve() -> None:
    out = [" ".join(border_chain(prefix_function(word)))
           for word in sys.stdin.buffer.read().split()]
    print("\n".join(out))


if __name__ == "__main__":
    solve()
